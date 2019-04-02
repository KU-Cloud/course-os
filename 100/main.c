/**
 * There's Always a Slight Duplication of Efforts 3.
 *
 * By walking through this example you’ll learn:
 * - The presence of overhead due to locks.
 * 
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h> 
#include <time.h>

int stick_this_thread_to_core(int core_id);
long timediff(clock_t t1, clock_t t2);

#define NUM_THREADS 100
#define NUM_TASKS 100000

static int cnt = 0;
pthread_mutex_t mutex;

void* worker_without_lock(void* arg){
    stick_this_thread_to_core(arg);
    for(int i = 0; i < NUM_TASKS; i++){
        cnt++;
    }
}

void* worker_with_lock(void* arg){
    stick_this_thread_to_core(arg);
    for(int i = 0; i < NUM_TASKS; i++){
        pthread_mutex_lock(&mutex);
        cnt++;
        pthread_mutex_unlock(&mutex);
    }
}


//
// There are no errors to fix.
// Just see the results.
//
int main(int argc, char* argv[]){
    pthread_t tids[NUM_THREADS];
    int status;
    time_t t1, t2, rst[2];
    void* (*trg[2])(void*) = {
        worker_with_lock,
        worker_without_lock
    };

    pthread_mutex_init(&mutex, NULL);

    for(int round = 0; round < 3; round++){
        printf("\nRound %d\n", round);

        t1 = clock();
        for(int i = 0; i < NUM_THREADS; i++){
            status = pthread_create(&tids[i], NULL, trg[round % 2], i);

            if(status != 0){
                printf("WTF?");
                return -1;
            }
        }
        
        for(int i = 0; i < NUM_THREADS; i++){
            pthread_join(tids[i], NULL);
        }

        t2 = clock();
        rst[round % 2] = timediff(t1, t2);



        t1 = clock();
        for(int i = 0; i < NUM_THREADS; i++){
            status = pthread_create(&tids[i], NULL, trg[(round + 1) % 2], i);

            if(status != 0){
                printf("WTF?");
                return -1;
            }
        }
        
        for(int i = 0; i < NUM_THREADS; i++){
            pthread_join(tids[i], NULL);
        }

        t2 = clock();
        rst[(round + 1) % 2] = timediff(t1, t2);

        printf("with lock: \t%lu\nwithout lock:\t%lu\n", rst[0], rst[1]);
    }

    return 0;
}



int stick_this_thread_to_core(int core_id) {
   int num_cores = sysconf(_SC_NPROCESSORS_ONLN);

   cpu_set_t cpuset;
   CPU_ZERO(&cpuset);
   CPU_SET(core_id % num_cores, &cpuset);

   pthread_t current_thread = pthread_self();    
   return pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
}

long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}
