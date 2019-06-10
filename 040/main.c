/**
 * Keep Running Your Process.
 *
 * By walking through this example you’ll learn:
 * - How to use execl() while keep your process using fork().
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    pid_t pid = fork();

    switch (pid)
    {
        default:
            // HINT: The parent process should fall into this scope.
            printf("I'm your father.\n");
            sleep(3);
            break;

        case 0:
            sleep(1);
            // HINT: The child process should fall into this scope.
            printf("I'm sorry, but I'm not Luke. I'm...");
            // fflush(FILE *stream) flushed the output buffer of a stream
            // 즉, 다음 데이터를 입력받기 전, 버퍼에 남아 있는 데이터를 지우기 위해 사용된다.
            // returns zero value on success, If an error occurs, EOF is returned
            fflush(stdout);

            sleep(1); // for dramatic effect

            // HINT: The /usr/bin/whoami should be executed.
            execl("/usr/bin/whoami", "whoami", NULL);

            // Notice that there is no break here.
            // Why?

        case -1:
            printf("WTF?");
            return -1;
            break;
    }
}
