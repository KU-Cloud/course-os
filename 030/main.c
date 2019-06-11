/**
 * Basic execl() Usage.
 *
 * By walking through this example you’ll learn:
 * - How to use execl().
 * - What happens to the process that invoked execl().
 * 
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    printf("%s executing `ls -l`.\n", "Before");

    // HINT: The /bin/ls -l should be executed.
    execl("/bin/ls", "ls", "-l", NULL);

    printf("%s executing `ls -l`.\n", "After");

    return 0;
}
