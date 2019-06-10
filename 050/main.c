/**
 * Allow Perseverance to Finish Its Work.
 *
 * By walking through this example you’ll learn:
 * - In the parent process, wait for the child process to complete its work.
 * - How to use wait().
 * 
 *  wait(int *statloc) 함수를 사용해, 자식 프로세스가 종료될때 까지 기다린다.
 *  1. 자식 프로세스가 동작 중이면 호출이 차단되므로, 상태를 얻을 때 까지 대기
 *  2. wait() 함수 호출자가 시그널을 받을 때까지 대기
 *  3. 자식 프로세스가 종료되면 즉시 호출이 반환되어 상태를 얻고, 자식 프로세스의 pid를 반환
 *  4. 자식 프로세스가 없다면 에러값을 반환
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
