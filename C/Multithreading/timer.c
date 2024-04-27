#include "timer.h"


void start_timer()
{
    pthread_once(&timer_once, create_key);

    struct timespec *start_time = pthread_getspecific(timer_key);
    if (start_time == NULL)
    {
        start_time = malloc(sizeof(struct timespec));
        pthread_setspecific(timer_key, start_time);
    }

    struct timespec current_timer;
    clock_gettime(CLOCK_MONOTONIC, &current_timer);
    *start_time = current_timer;
}


double stop_timer()
{
    struct timespec *start_time = pthread_getspecific(timer_key);
    if (start_time == NULL)
    {
        return 0;
    }

    struct timespec stop_time;
    clock_gettime(CLOCK_MONOTONIC, &stop_time);
    
    double elapsed_time = (stop_time.tv_sec - start_time->tv_sec) * 1e3; 
    elapsed_time += (stop_time.tv_nsec - start_time->tv_nsec) / 1e6;
    return elapsed_time; 
}


static void create_key(void)
{
    pthread_key_create(&timer_key , free_memory);
}


static void free_memory(void *buffer)
{
    free(buffer);
}
