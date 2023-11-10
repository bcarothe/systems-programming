#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <utmp.h>

#define DEFAULT_SLEEP_TIME 300
#define INITIAL_USERS_SIZE 50

char **users;
int utmpUserSize;

int main(int argc, char **argv) {
    int sleepTime = DEFAULT_SLEEP_TIME;

    users = malloc(sizeof(char *) * (INITIAL_USERS_SIZE)); // Creates elements (for each name) of users
    users[INITIAL_USERS_SIZE - 1] = '\0'; // Sets last element to null

    // int i;
    // for (i = 0; i < INITIAL_USERS_SIZE; i++) { // For each element
    //     users[i] = malloc(UT_NAMESIZE); // Allocate memory to each user
    //     member

    //     // free(users[i]); // free the memory pointer to by each pointer
    // }

    if (argc == 1) {          // If no arguments provided
        printf("No arguments provided\n");
        
    } else {  // If arguments provided

        int startIndex = 1;
        if (isNumber(argv[1]) == 1) {   // If number is provided in the argument
            sleepTime = atoi(argv[1]);  // Sets interval time in seconds
            startIndex = 2;  // Adjusts startIndex to account for time argument
        }

        while (1) {
            dumpfile(UTMP_FILE); // UTMP_FILE = /var/run/utmp

            // // For debug
            // {
            //     int i;
            //     for (i = 0; i < INITIAL_USERS_SIZE; ++i) {
            //         printf("user %i: %s\n", i, users[i]);
            //     }
            // }

            int i = startIndex;
            for (; i < argc; ++i) {  // For each argument

                int j;
                for (j = 0; j < INITIAL_USERS_SIZE;
                     ++j) {  // For each user in users

                    // printf("Comparing %s with %s: %i\n", users[j], argv[i],
                    // strcmp(users[j], argv[i]));

                    // Compares names to only specified names in arguments
                    if (strcmp(users[j], argv[i]) == 0) {
                        printf("%s ", users[j]);
                        break;
                    }
                }
            }

            printf("are logged in\n");
            i = 0;
            sleep(sleepTime);
        }
    }
}

// Checks if input is a number
int isNumber(char number[]) {
    int i = 0;

    // Checks for negative number
    if (number[0] == '-') {
        i = 1;
        printf("Number cannot be negative\n");
        exit(-1);
    }
    // Checks each digit for number
    for (; number[i] != 0; i++) {
        // if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i])) {
            return 0;
        }
    }
    return 1;
}

dumpfile(fn) char *fn;
/*
 *	open file and dump records
 */
{
    struct utmp utrec;
    int fd;

    fd = open(fn, 0);
    if (fd == -1) {
        perror(fn);
        return;
    }

    int i = 0;
    while (read(fd, &utrec, sizeof(utrec)) == sizeof(utrec)) {
        i += show_utrec(&utrec, i);
    }
    close(fd);

    utmpUserSize = i;  // Sets size of users
}

int show_utrec(rp, i) struct utmp *rp;
{
    if (rp->ut_type == USER_PROCESS) {
        users[i] = malloc(UT_NAMESIZE);
        strcpy(users[i], rp->ut_user);  // store data in that particular element
        return 1;
    }
    return 0;
}