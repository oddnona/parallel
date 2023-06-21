#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>
#include "linkedlist.h"
#include "hashtable.h"
#include "stringmanipulation.h"
#include "stringlist.h"
#include "pw_helpers.h"

#define SENDTASKTAG 10
#define DONETASKTAG 11
#define SERVER_ID 0

#define debug(...) fprintf(stderr, __VA_ARGS__);


void executeTask1(struct users users, struct stringList *top250) {

    debug("HERE!\n");
    ///////////////////////////////////////////////////////////////////
    // We will now start to do the real work
    ///////////////////////////////////////////////////////////////////

    // The provided password guessing strategy is very simple:
    // We will try the top 250 passwords, and all user name (parts)
    // In addition, we will try to uppercase and capitalized versions
    // of these lists and try those as passwords guesses.

    tryPasswords(top250, users.passwords, users.hashSetting);
    tryPasswords(users.names[0], users.passwords, users.hashSetting);
    tryPasswords(users.names[1], users.passwords, users.hashSetting);
    tryPasswords(users.names[2], users.passwords, users.hashSetting);
    tryPasswords(users.names[3], users.passwords, users.hashSetting);

    struct stringList *uppercase250 = uppercaseList(top250);
    struct stringList *uppercaseName0 = uppercaseList(users.names[0]);
    struct stringList *uppercaseName1 = uppercaseList(users.names[1]);
    struct stringList *uppercaseName2 = uppercaseList(users.names[2]);
    struct stringList *uppercaseName3 = uppercaseList(users.names[3]);

    struct stringList *capital250 = capitalList(top250);
    struct stringList *capitalName0 = capitalList(users.names[0]);
    struct stringList *capitalName1 = capitalList(users.names[1]);
    struct stringList *capitalName2 = capitalList(users.names[2]);
    struct stringList *capitalName3 = capitalList(users.names[3]);

    tryPasswords(uppercase250, users.passwords, users.hashSetting);
    tryPasswords(uppercaseName0, users.passwords, users.hashSetting);
    tryPasswords(uppercaseName1, users.passwords, users.hashSetting);
    tryPasswords(uppercaseName2, users.passwords, users.hashSetting);
    tryPasswords(uppercaseName3, users.passwords, users.hashSetting);

    tryPasswords(capital250, users.passwords, users.hashSetting);
    tryPasswords(capitalName0, users.passwords, users.hashSetting);
    tryPasswords(capitalName1, users.passwords, users.hashSetting);
    tryPasswords(capitalName2, users.passwords, users.hashSetting);
    tryPasswords(capitalName3, users.passwords, users.hashSetting);

    ///////////////////////////////////////////////////////////////////
    // Cleanup
    ///////////////////////////////////////////////////////////////////

    // Clean password list
    freeStringList(uppercase250);
    freeStringList(uppercaseName0);
    freeStringList(uppercaseName1);
    freeStringList(uppercaseName2);
    freeStringList(uppercaseName3);
    freeStringList(capital250);
    freeStringList(capitalName0);
    freeStringList(capitalName1);
    freeStringList(capitalName2);
    freeStringList(capitalName3);

    
}
void executeTask2(struct users users, struct stringList *books) {

    ///////////////////////////////////////////////////////////////////
    tryPasswords(books, users.passwords, users.hashSetting);
    struct stringList *uppercasebooks = uppercaseList(books);
    struct stringList *capitalbooks = capitalList(books);
    tryPasswords(uppercasebooks, users.passwords, users.hashSetting);
    tryPasswords(capitalbooks, users.passwords, users.hashSetting);
    ///////////////////////////////////////////////////////////////////
    // Clean password list
    freeStringList(uppercasebooks);
    freeStringList(capitalbooks);
    
}
void executeTask3(struct users users, struct stringList *top250){

    char *xor = "xor";
    char end = '\0';
    struct stringList *t250xor = manipulateList(top250, end, xor, 1);
    tryPasswords(t250xor, users.passwords, users.hashSetting);
    freeStringList(t250xor);
}

void executeTask4(struct users users, struct stringList *books){

    char *xor = "xor";
    char end = '\0';
    struct stringList *booksxor = manipulateList(books, end, xor, 1);
    tryPasswords(booksxor, users.passwords, users.hashSetting);
    freeStringList(booksxor);
}

void executeTask5(struct users users){

    char *xor = "xor";
    char end = '\0';
    struct stringList *Name0xor = manipulateList(users.names[0], end, xor, 1);
    struct stringList *Name1xor = manipulateList(users.names[1], end, xor, 1);
    struct stringList *Name2xor = manipulateList(users.names[2], end, xor, 1);
    struct stringList *Name3xor = manipulateList(users.names[3], end, xor, 1);

    tryPasswords(Name0xor, users.passwords, users.hashSetting);
    tryPasswords(Name1xor, users.passwords, users.hashSetting);
    tryPasswords(Name2xor, users.passwords, users.hashSetting);
    tryPasswords(Name3xor, users.passwords, users.hashSetting);
    freeStringList(Name0xor);
    freeStringList(Name1xor);
    freeStringList(Name2xor);
    freeStringList(Name3xor);
}

void executeTask6(struct users users, struct stringList *top250){

    char *zorz = "zorz";
    char end = '\0';
    struct stringList *t250zorz = manipulateList(top250, end, zorz, 1);
    tryPasswords(t250zorz, users.passwords, users.hashSetting);
    freeStringList(t250zorz);
}

void executeTask7(struct users users, struct stringList *books){

    char *zorz = "zorz";
    char end = '\0';
    struct stringList *bookszorz = manipulateList(books, end, zorz, 1);
    tryPasswords(bookszorz, users.passwords, users.hashSetting);
    freeStringList(bookszorz);
}

void executeTask8(struct users users){

    char *zorz = "zorz";
    char end = '\0';
    struct stringList *Name0zorz = manipulateList(users.names[0], end, zorz, 1);
    struct stringList *Name1zorz = manipulateList(users.names[1], end, zorz, 1);
    struct stringList *Name2zorz = manipulateList(users.names[2], end, zorz, 1);
    struct stringList *Name3zorz = manipulateList(users.names[3], end, zorz, 1);

    tryPasswords(Name0zorz, users.passwords, users.hashSetting);
    tryPasswords(Name1zorz, users.passwords, users.hashSetting);
    tryPasswords(Name2zorz, users.passwords, users.hashSetting);
    tryPasswords(Name3zorz, users.passwords, users.hashSetting);
    freeStringList(Name0zorz);
    freeStringList(Name1zorz);
    freeStringList(Name2zorz);
    freeStringList(Name3zorz);
}

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


    ///////////////////////////////////////////////////////////////////
    // We now set up the local environment
    ///////////////////////////////////////////////////////////////////
    
    // Read the password/shadow files and parse all input
    char *passwdPath = argv[1];
    char *shadowPath = argv[2];

    struct users users = parseInput(passwdPath, shadowPath, false);

    // Read top 250 passwords
    struct stringList *top250 = readStringsFile("Files/top250.txt", MAX_PW_LENGTH);
    struct stringList *books = readStringsFile("Files/books.txt", MAX_PW_LENGTH);

    ///////////////////////////////////////////////////////////////////
    // Setup Master Worker
    ///////////////////////////////////////////////////////////////////
    int nr_tasks = 8;
    int task = -1;
    if (rank == SERVER_ID) {
        task = 1;
        for(int i=1; i<nrProcessors; i++){
            MPI_Send(&task, 1, MPI_INT, i, SENDTASKTAG, MPI_COMM_WORLD); 
            task++;
        }

        while (task <= nr_tasks) {
            MPI_Recv(&rankId, 1, MPI_INT, MPI_ANY_SOURCE, DONETASKTAG, MPI_COMM_WORLD, NULL);
            MPI_Send(&task, 1, MPI_INT, rankId, SENDTASKTAG, MPI_COMM_WORLD);
            task++;
        }

        task=-1;
        for(int i=1; i<nrProcessors; i++){
            MPI_Send(&task, 1, MPI_INT, i, SENDTASKTAG, MPI_COMM_WORLD); 
        }
               

    } else {
        do
        {
            MPI_Recv(&task, 1, MPI_INT, SERVER_ID, SENDTASKTAG, MPI_COMM_WORLD, NULL);
            switch (task)
            {
                case 1:
                    executeTask1(users, top250);
                    break;
                case 2:
                    executeTask2(users, books);
                    break;
                case 3:
                    executeTask3(users, top250);
                    break;
                case 4:
                    executeTask4(users, books);
                    break;
                case 5:
                    executeTask5(users);
                    break;
                case 6:
                    executeTask6(users, top250);
                    break;
                case 7:
                    executeTask7(users, books);
                    break;
                case 8:
                    executeTask8(users);
                    break;
                default:
                    break;
            }
            MPI_Send(&rank, 1, MPI_INT, SERVER_ID, DONETASKTAG, MPI_COMM_WORLD);
        } while (task!=-1);
        
        
    }
    // Free users struct/information
    freeUserData(users);
    freeStringList(top250);
    freeStringList(books);
    MPI_Finalize();
}
