/**
 * Basic fork() Usage 2.
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

int main(int argc, char* argv[]){
    pid_t pid;
    int val = 1;

    printf("The value is %d\n", val);
    
    pid = fork();

    if(<?1/>){
        // HINT: The parent process should fall into this scope.
        val++;
    } else if(<?2/>) {
        // HINT: The child process should fall into this scope.
        sleep(1);
        val--;
    } else {
        printf("WTF?");
        return -1;
    }
    
    printf("The value is %d in %s.\n", val, <?3/> ? "child" : "parent");

    return 0;
}
