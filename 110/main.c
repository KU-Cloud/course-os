/**
 * Do Your Job and I'll Do Mine 1.
 *
 * By walking through this example you’ll learn:
 * - How to use thread_detach().
 * - How to wait detached thread using shared variable.
 * 
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

    status = pthread_create(&tid, NULL, boss, NULL);

    if (status != 0)
    {
        printf("WTF?");
        return -1;
    }

    pthread_join(tid, NULL);

    // OBJECT: The main thread should not be exited until all `worker`s have finished.
    // 
    // HINT: The `main` thread cannot wait for `worker` threads detached by `boos`.
    // HINT: Is there any information about remaining tasks that can be
    //       referenced in the `main` thread?
    while (cnt_task)

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
