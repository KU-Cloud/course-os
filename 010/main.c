/**
 * Basic fork() Usage 1.
 *
 * By walking through this example you’ll learn:
 * - How to use fork().
 * - How to distinguish parent and child process.
 * - What happens to variables that reside in various scopes.
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

const int SEVEN_AND_A_HALF_MILLION_YEARS = 3;
const int A_DAY = 1;

// Allocated in data segment.
static int the_answer = 0;

int main(int argc, char* argv[]){
    // Allocated in stack segment.
    int arthur = 0;
    
    pid_t pid;

    switch(pid = fork()){
        default:
            // HINT: The parent process should fall into this scope.
            the_answer = 42;
            arthur = 6 * 9;
            sleep(SEVEN_AND_A_HALF_MILLION_YEARS);
            break;
        case 0:
            // HINT: The child process should fall into this scope.
            sleep(A_DAY * 2);
            break;
        case -1:
            printf("WTF?");
            return -1;
            break;
    }

    printf("My pid is %ld (%s)\n", (long)getpid(), pid == 0 ? "child" : "parent");
    printf("The answer to the ultimate question of life the universe and everything is %d.\n", the_answer);
    printf("But Arthur replied that it was %d.\n\n", arthur);

    return 0;
}
