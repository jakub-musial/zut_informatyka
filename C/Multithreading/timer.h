#ifndef TIMER_H
#define TIMER_H
 
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
 
 
static pthread_key_t timer_key;
static pthread_once_t timer_once = PTHREAD_ONCE_INIT;
 
void start_timer();
double stop_timer();
static void create_key(void);
static void free_memory(void *buffer);
 
#endif // TIMER_H