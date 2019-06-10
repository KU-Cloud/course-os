/**
 * Do Your Job and I'll Do Mine 1.
 *
 * By walking through this example you’ll learn:
 * - How to use thread_detach().
 * - How to wait detached thread using shared variable.
 * 
 * pthread_detach() 함수는, 스레드에 할당된 리소스가 종료 시 회수가능하다는 것을
 * 시스템에 알리기 위해 사용된다. 이 함수는 다른 스레드가 종료상태를 필요로 하지 않을 때, 사용해야만 한다.
 * 
 * 스레드가 detach되지 않고 종료되면, 스레드의 작업이 해방되어, thread_join() 또는 thread_detach()에 의해
 * 스레드가 파기될 때 까지, 힙과 OS 레벨의 오브젝트도 포함한 모든 리소스가 남아버리게 된다.
 */

#include <stdio.h>
#include <stdatomic.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#define NUM_WORKERS 3
#define NUM_PERSONAL_TASK 3
#define NUM_TOTAL_TASK (NUM_WORKERS * NUM_PERSONAL_TASK)

static _Atomic int cnt_task = NUM_TOTAL_TASK;

void do_job(char* actor);
void go_home(char* actor);
void* worker(void* arg);
void* boss(void* arg);

int main(int argc, char* argv[])
{
    pthread_t tid;
    int status;

    // 스레드 생성, NULL을 boss 함수에 넘겨줌
    status = pthread_create(&tid, NULL, boss, NULL);

    if (status != 0)
    {
        printf("WTF?");
        return -1;
    }

    pthread_join(tid, NULL);

    // OBJECT: The main thread should not be exited until all `worker`s have finished.
    // 
    // HINT: The `main` thread cannot wait for `worker` threads detached by `boss`.
    // HINT: Is there any information about remaining tasks that can be
    //       referenced in the `main` thread?
    while(cnt_task);

    return 0;
}



void do_job(char* actor){
    cnt_task--;
    printf("[%s] working...\n", actor);
}

void go_home(char* actor){
    printf("[%s] So long suckers!\n", actor);
}

void* worker(void* arg)
{
    char act[20];
    // sprintf(버퍼 변수, 포맷, 가변 파라미터)
    sprintf(act, "%s%d", "worker", (int)arg);

    for(int i = 0; i < 3; i++)
    {
        sleep(1);
        do_job(act);
    }
    
    pthread_exit(NULL);
}

void* boss(void* arg)
{
    pthread_t tid;
    int status;
    for(int i = 0; i < NUM_WORKERS; i++)
    {
        status = pthread_create(&tid, NULL, worker, i);

        if (status != 0)
        {
            printf("WTF?");
            return -1;
        }

        pthread_detach(tid);
    }

    go_home("like a boss");
    pthread_exit(NULL);
}
