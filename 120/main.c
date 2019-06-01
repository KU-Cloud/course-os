/**
 * Do Your Job and I'll Do Mine 2.
 *
 * By walking through this example you’ll learn:
 * - How to wait detached thread using mutex.
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
pthread_mutex_t task_done;

void do_job(char* actor);
void go_home(char* actor);
void* worker(void* arg);
void* boss(void* arg);

//
// OBJECT: The main thread should not be exited until all `worker`s have finished.
//
// HINT: The thread `boss` locks `task_done`.
// HINT: How to make `main` thread wait for all `worker`s.
// HINT: Who needs to release the lock and when should the lock be released?
//
// There are no blank hints in this example.
// Good luck.
//
// PS. Use mutex not `sleep` related function.
//
int main(int argc, char* argv[])
{
    pthread_t tid;
    int status;

    pthread_mutex_init(&task_done, NULL);

    status = pthread_create(&tid, NULL, boss, NULL);

    if (status != 0)
    {
        printf("WTF?");
        return -1;
    }

    pthread_join(tid, NULL);

    printf("Remaining task(s): %d\n", cnt_task);

    return 0;
}



void do_job(char* actor){
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
        pthread_mutex_lock(&task_done);
        do_job(act);
        pthread_mutex_unlock(&task_done);
    }
    
    sleep(0);
    pthread_exit(NULL);
}

void* boss(void* arg)
{
    pthread_t tid;
    int status;

    pthread_mutex_lock(&task_done);

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
