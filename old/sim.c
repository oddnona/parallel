#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOX_LENGTH 10.0       // Box length
#define DT 1.0E-1             // Time step size
#define PARTICLE_MASS 1.0E-3  // Particle mass
#define SIGMA 1.0E-2          // Particle size

/**
 * @brief Macro for easy termination in case of errors. Usage is similar to printf:
 * FATAL("This prints the number 5 and exits with an error code: %d\n", 5);
 */
#define FATAL(fmt, ...)                                                                                          \
  do {                                                                                                           \
    fprintf(stderr, "Fatal error: %s in %s() on line %d:\n\t" fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
    exit(EXIT_FAILURE);                                                                                          \
  } while (0)

typedef struct ThreadArgs {
    int *arr;
    int n;
    int t_id;
} ThreadArgs ;

ThreadArgs *create_args(int *arr, int n, int t_id) {
    ThreadArgs *args = malloc(sizeof(ThreadArgs));
    args->arr = arr;
    args->n = n;
    args->t_id = t_id;
    return args;
}

/**
 * @brief 3D vector.
 */
typedef struct vec3 {
  float x;
  float y;
  float z;
} vec3;

/**
 * @brief A particle consisting of a position, velocity and force.
 */
typedef struct Particle {
  vec3 pos;  // Position
  vec3 vel;  // Velocity
} Particle;

/**
 * @brief Reads input particles from a given file. The first line of the file is the number of particles N. The next N
 * lines each contains 6 floats: the first 3 are the initial position of the particle, the next 3 are the current
 * velocity of the particle.
 *
 * @param input_file Input file.
 * @param num_particles This pointer will be updated with the number of particles found in the file.
 * @return Particle* Array containing the particles from the file.
 */
Particle *read_input(FILE *input_file, int *num_particles) {
  int n, num_read;
  num_read = fscanf(input_file, "%d\n", &n);
  assert(num_read == 1);
  Particle *particles = malloc(n * sizeof(Particle));
  for (int i = 0; i < n; i++) {
    num_read = fscanf(input_file, "%f %f %f ", &particles[i].pos.x, &particles[i].pos.y, &particles[i].pos.z);
    assert(num_read == 3);
    num_read = fscanf(input_file, "%f %f %f ", &particles[i].vel.x, &particles[i].vel.y, &particles[i].vel.z);
    assert(num_read == 3);
  }
  *num_particles = n;
  return particles;
}

/**
 * @brief Saves the state of all particles to the provided file.
 *
 * @param file File to save the particle data to.
 * @param particles The particles to save.
 * @param num_particles Number of particles to save.
 */
void save_particles(FILE *file, Particle *particles, int num_particles) {
  fprintf(file, "%d\n", num_particles);
  for (int i = 0; i < num_particles; i++) {
    fprintf(file, "%lf %lf %lf ", particles[i].pos.x, particles[i].pos.y, particles[i].pos.z);
    fprintf(file, "%lf %lf %lf\n", particles[i].vel.x, particles[i].vel.y, particles[i].vel.z);
  }
}

/**
 * @brief Calculates the Lennard-Jones potential between two particles.
 * The energy potential is described as
 *      U(r) = 4 * (s^12/r^12 - s^6/r^6)
 * where r is the distance between the two particles and s is the sigma value that represents the size of the particle.
 *
 * @param r2 Squared distance between two particles.
 * @return float The Lennard-Jones potential between two particles.
 */
float lj_potential(float r2) {
  float r6 = r2 * r2 * r2;
  float r12 = r6 * r6;

  float sigma2 = SIGMA * SIGMA;
  float sigma6 = sigma2 * sigma2 * sigma2;
  float sigma12 = sigma6 * sigma6;
  return 4.0 * (sigma12 / r12 - sigma6 / r6);
}

/**
 * @brief Calculates the force between two particles based on the Lennard-Jones potential.
 * The energy potential is described as
 *      U(r) = 4 * (s^12/r^12 - s^6/r^6)
 * where r is the distance between the two particles and s is the sigma value that represents the size of the particle.
 * The force is calculated as F(r) = - dU(r)/dr = 24 * ((2s^12)/r^13 - (s^6)/r^7)
 *
 * @param r Distance between two particles.
 * @return float The amount of force the two particles would exert on each other.
 */
float lj_potential_force(float r) {
  float r2 = r * r;
  float r6 = r2 * r2 * r2;
  float r12 = r6 * r6;

  float sigma2 = SIGMA * SIGMA;
  float sigma6 = sigma2 * sigma2 * sigma2;
  float sigma12 = sigma6 * sigma6;
  return 24.0 * (2.0 * sigma12 / r12 - 1.0 * sigma6 / r6) / r;
}

/**
 * @brief Performs a molecular dynamics simulation with the provided particles.
 *
 * @param particles The particles to simulate.
 * @param n Number of particles.
 * @param time_steps Number of time steps to simulate.
 * @param num_threads Number of threads to use for parallel execution.
 * @return float The total amount of energy in the system after all time steps have been simulated.
 */
float simulate(Particle *particles, int n, int time_steps, int num_threads) {
  vec3 *forces = malloc(n * sizeof(vec3));
  for (int t = 0; t < time_steps; t++) {
    // Reset the forces
    memset(forces, 0, n * sizeof(vec3));
    // Calculate forces
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        // Distance between particles
        float dx = particles[i].pos.x - particles[j].pos.x;
        float dy = particles[i].pos.y - particles[j].pos.y;
        float dz = particles[i].pos.z - particles[j].pos.z;
        // Periodic boundary condition
        if (dx > 0.5 * BOX_LENGTH) dx -= BOX_LENGTH;
        if (dx < -0.5 * BOX_LENGTH) dx += BOX_LENGTH;
        if (dy > 0.5 * BOX_LENGTH) dy -= BOX_LENGTH;
        if (dy < -0.5 * BOX_LENGTH) dy += BOX_LENGTH;
        if (dz > 0.5 * BOX_LENGTH) dz -= BOX_LENGTH;
        if (dz < -0.5 * BOX_LENGTH) dz += BOX_LENGTH;
        // Calculate straight distance
        float r = sqrtf(dx * dx + dy * dy + dz * dz);
        float force = lj_potential_force(r);
        forces[i].x += force * dx;
        forces[i].y += force * dy;
        forces[i].z += force * dz;
        forces[j].x -= force * dx;
        forces[j].y -= force * dy;
        forces[j].z -= force * dz;
      }
    }

    // Verlet Integration
    for (int i = 0; i < n; i++) {
      particles[i].pos.x += particles[i].vel.x * DT + 0.5 * forces[i].x / PARTICLE_MASS * DT * DT;
      particles[i].pos.y += particles[i].vel.y * DT + 0.5 * forces[i].y / PARTICLE_MASS * DT * DT;
      particles[i].pos.z += particles[i].vel.z * DT + 0.5 * forces[i].z / PARTICLE_MASS * DT * DT;
      particles[i].vel.x += 0.5 * forces[i].x / PARTICLE_MASS * DT;
      particles[i].vel.y += 0.5 * forces[i].y / PARTICLE_MASS * DT;
      particles[i].vel.z += 0.5 * forces[i].z / PARTICLE_MASS * DT;
    }
  }

  float potential_energy = 0.0;
  float kinetic_energy = 0.0;
  // Calculate the total amount of energy
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      float dx = particles[i].pos.x - particles[j].pos.x;
      float dy = particles[i].pos.y - particles[j].pos.y;
      float dz = particles[i].pos.z - particles[j].pos.z;
      // Periodic boundary condition
      if (dx > 0.5 * BOX_LENGTH) dx -= BOX_LENGTH;
      if (dx < -0.5 * BOX_LENGTH) dx += BOX_LENGTH;
      if (dy > 0.5 * BOX_LENGTH) dy -= BOX_LENGTH;
      if (dy < -0.5 * BOX_LENGTH) dy += BOX_LENGTH;
      if (dz > 0.5 * BOX_LENGTH) dz -= BOX_LENGTH;
      if (dz < -0.5 * BOX_LENGTH) dz += BOX_LENGTH;
      float r2 = dx * dx + dy * dy + dz * dz;
      potential_energy += lj_potential(r2);
    }

    kinetic_energy += 0.5 * PARTICLE_MASS *
                      (particles[i].vel.x * particles[i].vel.x + particles[i].vel.y * particles[i].vel.y +
                       particles[i].vel.z * particles[i].vel.z);
  }
  free(forces);
  return potential_energy + kinetic_energy;
}

/**
 * @brief Molecular Dynamics simulation. Needs at least arguments: a number of time-steps to simulate and a number of
 * threads. Optionally, an input file can be given as final argument.
 * Usage: ./a.out <time-steps> <num-threads> [input_file]
 * Example usage: ./a.out 5 2
 * This will read the configuration from stdin and perform the simulation for 5 time steps. In the serial
 * version, the number of threads argument is unused.
 * Recommded Compilation: gcc -Wall -pedantic -O3 sim.c -lm
 * Debug Compilation: gcc -Wall -pedantic -g sim.c -lm
 * When evaluating performance: always compile with the -O3 flag
 *
 * @param argc Number of arguments.
 * @param argv Arguments. Two arguments are expected: a number of time-step and number of threads (in
 * that order). A third argument - an input file - is optional.
 * @return int Exit code.
 */
int main(int argc, char *argv[]) {
  // Argument parsing
  if (argc != 3 && argc != 4) {
    fprintf(stderr, "Usage: ./a.out <time-steps> <num-threads> [input_file]\n");
    exit(EXIT_SUCCESS);
  }
  int time_steps = atoi(argv[1]);
  int num_threads = atoi(argv[2]);
  char *input_file_path = argv[3];

  // Input reading
  int num_particles;
  fprintf(stderr, "Reading input...\n\n");
  Particle *particles;
  if (input_file_path == NULL) {
    particles = read_input(stdin, &num_particles);
  } else {
    FILE *input_file = fopen(input_file_path, "r");
    if (input_file == NULL) {
      FATAL("Cannot open file %s\n", input_file_path);
    }
    particles = read_input(input_file, &num_particles);
    fclose(input_file);
  }

  // Timer start
  fprintf(stderr, "Starting molecular dynamics simulation using %d threads\n", num_threads);
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  // Simulation
  float total_energy = simulate(particles, num_particles, time_steps, num_threads);

  // Timer end
  clock_gettime(CLOCK_MONOTONIC, &end);
  double time_spent = (end.tv_sec - start.tv_sec);
  time_spent += (end.tv_nsec - start.tv_nsec) / 1e9;

  // Summary
  fprintf(stderr, "Simulation of %d particles complete -- Took: %f seconds.\n\n", num_particles, time_spent);
  fprintf(stdout, "Total energy: %.2lf\n", total_energy);
  fprintf(stderr, "Saving particles...\n");
  save_particles(stdout, particles, num_particles);

  free(particles);
  return EXIT_SUCCESS;
}
