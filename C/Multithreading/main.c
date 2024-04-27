#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <signal.h>
#include <unistd.h>
#include <time.h> 
#include <sys/wait.h>
#include <pthread.h>
#include "timer.h"


typedef struct thread_data {
    pthread_t thread_id;
    int lifetime;
    int is_active;
} thread_data_t;

void signal_handler(int signum);
void *thread_routine(void *arg);


int main(int argc, char **argv)
{
    int thread_ammount = 0, max_life = 0, ret;
    while ((ret = getopt(argc, argv, "t:m:")) != -1)
    {
        switch (ret)
        {
            case 't':
                thread_ammount = atoi(optarg);
                if (thread_ammount <= 0) {
                    perror("Wartosc t musi byc wieksza od 0.\n");
                    return EXIT_FAILURE;
                }
                break;
            case 'm':
                max_life = atoi(optarg);
                if (max_life <= 0) {
                    perror("Wartosc m musi byc wieksza od 0.\n");
                    return EXIT_FAILURE;
                }
                break;
            default: abort();
        }
    }

    // Ustaienie obsługi sygnału
    signal(SIGUSR1, signal_handler);

    // Utworzenie tablicy przechowującej informacje o wątkach
    thread_data_t *threads = malloc(sizeof(thread_data_t) * thread_ammount);

    // Tworzenie nowych wątków
    for (int i = 0; i < thread_ammount; i++)
    {
        threads[i].lifetime = rand() % max_life + 1;
        threads[i].is_active = 1;
        pthread_create(&(threads[i].thread_id), NULL, thread_routine, NULL);
        printf("[ %lu ] [ %d ]\n", threads[i].thread_id, threads[i].lifetime);
    }

    int finished_threads = 0;
    struct timespec start, current_time;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Główna pętla programu
    while (finished_threads < thread_ammount)
    {
        // Sprawdzenie ile czasu upłynęło
        clock_gettime(CLOCK_MONOTONIC, &current_time);
        int elapsed_time = current_time.tv_sec - start.tv_sec;

        for (int i = 0; i < thread_ammount; i++)
        {    
            if (threads[i].lifetime <= elapsed_time &&
                threads[i].is_active &&
                pthread_kill(threads[i].thread_id, SIGUSR1) == 0 && 
                pthread_join(threads[i].thread_id, NULL) == 0)
            {
                threads[i].is_active = 0;
                finished_threads++;
            }
        }
    }

    free(threads);
    return 0;
}


void signal_handler(int signum)
{
    if(signum == SIGUSR1)
    {
        double elapsed_time = stop_timer();

        printf("                              [ %lu ] [ %f ms]\n", pthread_self(), elapsed_time);

        pthread_exit(NULL);
    }
}


void *thread_routine(void *arg)
{
    start_timer();

    // Liczenie kolejnych wartości silni
    unsigned int i = 1;
    unsigned long long factorial = 1;
    while (1) {
        factorial *= i++;
    }
}