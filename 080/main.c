/**
 * There's Always a Slight Duplication of Efforts 1.
 *
 * By walking through this example you’ll learn:
 * - How to use pthread_join().
 * - What happens when multiple threads try to reference the same memory block.
 * 
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

int stick_this_thread_to_core(int core_id);

#define NUM_THREADS 100
#define NUM_TASKS 100000

static int cnt = 0;

void* worker(void* arg){
    stick_this_thread_to_core(arg);
    int progress;
    
    for(int i = 0; i < NUM_TASKS; i++){
        progress = cnt++;
    }

    pthread_exit(progress);
}

int main(int argc, char* argv[]){
    pthread_t tids[NUM_THREADS];
    int status;
    int progress = 0;

    for(int i = 0; i < NUM_THREADS; i++){
        // HINT: The thread that runs `worker` should be created.
        // HINT: The address of variable `i` should be passed when thread created.
        // HINT: Each thread descriptor should be stored appropriately.
        status = pthread_create(&tids[i], NULL, worker, &i);

        if(status != 0){
            printf("WTF?");
            return -1;
        }
    }

    // HINT: The main thread should not be exited until all `worker`s have finished.
    for(int i=0; i<NUM_THREADS; i++) {
        pthread_join(tids[i], NULL);
        // HINT: The variable `progress` should not be 0.
        printf("\r%d ", progress);

        fflush(stdout);
        usleep(10*1000); // 10ms
    }

    printf("\nexpectd: %d\n", NUM_THREADS * NUM_TASKS);
    printf("result: %d\n", cnt);

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
