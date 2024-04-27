#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <signal.h>
#include <unistd.h>
#include <time.h> 
#include <sys/wait.h>
 
 
int terminate_main_loop = 0;
int terminate_factorial = 0;
 
void create_child(int max_life);
void handle_SIGINT(int signum);
void handle_SIGALRM(int signum);
void handle_SIGRT(int signum, siginfo_t *info, void *context);
 
 
int main(int argc, char **argv)
{
    int wait_time = 0, max_life = 0, ret;
    while ((ret = getopt(argc, argv, "w:m:")) != -1)
    {
        switch (ret)
        {
            case 'w':
                wait_time = atoi(optarg);
                if (wait_time <= 0) {
                    perror("Wartosc w musi byc wieksza od 0.\n");
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
 
    // Obsługa sygnału SIGINT (CTRL+C)
    struct sigaction sa_int;
    sa_int.sa_handler = handle_SIGINT;
    sigaction(SIGINT, &sa_int, NULL);
    
    // Obsługa SIGALRM
    struct sigaction sa_alarm;
    sa_alarm.sa_handler = handle_SIGALRM;
    sa_alarm.sa_flags = SA_SIGINFO;
    sigaction(SIGALRM, &sa_alarm, NULL);
 
    // Obsługa sygnału czasu rzeczywistego
    struct sigaction sa_rt;
    sa_rt.sa_sigaction = handle_SIGRT;
    sa_rt.sa_flags = SA_SIGINFO;
    sigaction(SIGRTMIN, &sa_rt, NULL);

	unsigned int remaining_time = 0;

    // Główna pętla
    while (!terminate_main_loop)
    {   
        create_child(max_life);
        remaining_time = sleep(wait_time);
		while (remaining_time > 0){
			remaining_time = sleep(remaining_time);
		}
    }
 
    // Czekanie na zakończenie wszystkich uruchomionych do tej pory potomków
    while(waitpid(-1, NULL, WNOHANG) >=0);
    return 0;
}
 
void create_child(int max_life)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork fail");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // Proces potomny
    {
        srand(time(NULL));
        int random_value = rand() % max_life + 1;
 
        char time_buffer[50];
        time_t current_time = time(NULL);
        strftime(time_buffer, sizeof(time_buffer), "%c", localtime(&current_time));
 
        printf("[ %d ] [ %d ] [ %s ]\n", getpid(), random_value, time_buffer);
 
        alarm(random_value);
 
        union sigval sv;
        sv.sival_int = random_value;
 
        // Liczenie kolejnych wartości silni
        unsigned int i = 1;
        unsigned long long factorial = 1;
        while (!terminate_factorial) {
            factorial *= i++;
        }
 
        // Wysłanie sygnału czasu rzeczywisetgo do procesu rodzica
        sigqueue(getppid(), SIGRTMIN, sv);
        exit(EXIT_SUCCESS);
    }
}
 
void handle_SIGINT(int signum) {
  terminate_main_loop = 1;
}
 
void handle_SIGALRM(int signum) {
    terminate_factorial = 1;
}
 
void handle_SIGRT(int signum, siginfo_t *info, void *context) 
{
  char time_buffer[50];
  time_t end_time = time(NULL);
  strftime(time_buffer, sizeof(time_buffer), "%c", localtime(&end_time));
 
  printf("                              [ %d ] [ %d ] [ %s ]\n", info->si_pid, info->si_value.sival_int, time_buffer);
}