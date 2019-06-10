/**
 * Basic POSIX Thread (pthread) Usage 1.
 *
 * By walking through this example you’ll learn:
 * - How to use pthread_create().
 *   pthread_create(pthread_t * th_id, 속성(기본일 경우 NULL), void* 함수이름, 인자값)
 *   성공적으로 생성될 경우 0 반환
 * - How to use pthread_exit().
 *   pthread_exit(void * ret_value)
 *   현재 실행중인 쓰레드를 종료시킬 때 사용한다.
 * - How to use pthread_join().
 *   pthread_join(pthread_t th_id, 쓰레드의 리턴값 포인터)
 *   특정 pthread가 종료될 때 까지 기다리다가 종료시 자원 해제시킨다.
 * 쓰레드를 갖고 놀아보자!
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

// 닌자 쓰레드
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
    // pthread의 자료형
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
    pthread_join(tid, (void **)&from);

    // HINT: The variable `from` should not be empty.
    printf(" - from %s\n", from);

    printf("Knuc...kles.\n");

    return 0;
}
