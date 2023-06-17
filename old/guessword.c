#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "linkedlist.h"
#include "hashtable.h"
#include "stringmanipulation.h"
#include "stringlist.h"
#include "pw_helpers.h"

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

    ///////////////////////////////////////////////////////////////////
    // We now set up the local environment
    ///////////////////////////////////////////////////////////////////
    
    // Read the password/shadow files and parse all input
    char *passwdPath = argv[1];
    char *shadowPath = argv[2];

    struct users users = parseInput(passwdPath, shadowPath, false);

    // Read top 250 passwords
    struct stringList *top250 = readStringsFile("Files/top250.txt", MAX_PW_LENGTH);

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
    freeStringList(top250);
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

    // Free users struct/information
    freeUserData(users);
}
