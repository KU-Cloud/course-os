/**
 * Allow Perseverance to Finish Its Work.
 *
 * By walking through this example you’ll learn:
 * - In the parent process, wait for the child process to complete its work.
 * - How to use wait().
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



//
// Expected output:
//
// It breaks my heart to see my fellow zealots suffer on the battlefield
// But what if we dragoons went to their rescue?
// Duh! Ra! Goon!
//

int main(int argc, char* argv[]){
    pid_t pid;
    int status;

    printf("It breaks my heart to see my fellow zealots suffer on the battlefield.\n");
    printf("But what if we dragoons went to their rescue?\n");

    printf("Duh! ");
    fflush(stdout);

    pid = fork();

    if(pid > 0){
        // HINT: The parent process should fall into this scope.
        wait(&status);
        printf("Goon!\n");
    } else if(pid == 0){
        // HINT: The child process should fall into this scope.
        printf("Ra! ");
    } else {
        printf("WTF?");
        return -1;
    }

    return 0;
}
