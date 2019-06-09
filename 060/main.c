/**
 * Basic POSIX Thread (pthread) Usage 1.
 *
 * By walking through this example you’ll learn:
 * - How to use pthread_create().
 * - How to use pthread_exit().
 * - How to use pthread_join().
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

void* ninja(void* arg){
    printf("Who’s there?");
    fflush(stdout);

    pthread_exit("ninja");
}



//
// Expected output:
//
// Knock knock.
// Who's there? - from ninja
// Knuc...kles.
//

int main(int argc, char* argv[]){
    pthread_t tid;
    char* from = "";
    
    printf("Knock knock.\n");

    // HINT: The thread that runs `ninja` should be created.
    int status = pthread_create(&tid, NULL, ninja, NULL);

    if(status != 0){
        printf("WTF?");
        return -1;
    }

    // HINT: The main thread should not be exited until `ninja` has finished.
    pthread_join(tid, &from);

    // HINT: The variable `from` should not be empty.
    printf(" - from %s\n", from);

    printf("Knuc...kles.\n");

    return 0;
}
