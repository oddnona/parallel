#include "tasks.h"

#define SENDTASKTAG 10
#define DONETASKTAG 11
#define SERVER_ID 0 //master


/**
 * Our entrypoint. We require two arguments to our program: the paths to a passwd and
 * shadow file. The number of threads/processes is dictated by MPI, and is out of our
 * control at this point.
 * 
 * Run like: mpiexec -n <threads> ./guessword <passwd> <shadow>
 */
int main(int argc, char **argv) {
   
    // Check arguments
    if(argc != 3) {
        fprintf(stderr, "Usage: ./guessword <passwd> <shadow>");
        return EXIT_FAILURE;
    }
    MPI_Init(&argc, &argv);
    int nrProcessors, rank, rankId;
    MPI_Comm_size(MPI_COMM_WORLD, &nrProcessors);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // Read the password/shadow files and parse all input
    char *passwdPath = argv[1];
    char *shadowPath = argv[2];

    struct users users = parseInput(passwdPath, shadowPath, false);

    //lists of words used to compare and manipulate during tasks
    struct stringList *top250 = readStringsFile("Files/top250.txt", MAX_PW_LENGTH);
    struct stringList *books = readStringsFile("Files/books.txt", MAX_PW_LENGTH);
    struct stringList *years = readStringsFile("Files/years.txt", MAX_PW_LENGTH);

    ///////////////////////////////////////////////////////////////////
    // Setup Master Worker
    ///////////////////////////////////////////////////////////////////
    int nr_tasks = 39;  //number of tasks to be worked on
    int task = -1;
    if (rank == SERVER_ID) {   //the master has rank 0
        task = 1;
        for(int i=1; i<nrProcessors; i++){
            MPI_Send(&task, 1, MPI_INT, i, SENDTASKTAG, MPI_COMM_WORLD); //send tasks for all the other workers
            task++;
        }

        while (task <= nr_tasks) {
            MPI_Recv(&rankId, 1, MPI_INT, MPI_ANY_SOURCE, DONETASKTAG, MPI_COMM_WORLD, NULL); //master waits to be informed that tasks are done
            MPI_Send(&task, 1, MPI_INT, rankId, SENDTASKTAG, MPI_COMM_WORLD); //when a task is done, master gives the respective worker another task to do until all is done
            task++;
        }

        task=-1; 
        for(int i=1; i<nrProcessors; i++){
            MPI_Send(&task, 1, MPI_INT, i, SENDTASKTAG, MPI_COMM_WORLD); 
        } //master informs all the workers that the tasks are done in order to stop
               

    } else {
        do
        {
            MPI_Recv(&task, 1, MPI_INT, SERVER_ID, SENDTASKTAG, MPI_COMM_WORLD, NULL); //worker receives task message from master
            doWork(task, users, top250, books, years);  //worker completes the task
            MPI_Send(&rank, 1, MPI_INT, SERVER_ID, DONETASKTAG, MPI_COMM_WORLD); //worker informs the master that the task is done
        } while (task!=-1);
        
        
    }
    // cleanup
    freeUserData(users);
    freeStringList(top250);
    freeStringList(books);
    MPI_Finalize();
}
