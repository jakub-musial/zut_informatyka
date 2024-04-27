#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <getopt.h>
 
int main(int argc, char **argv)
{
    int v_flag = 0, t = 1, ret;
 
    while ((ret = getopt(argc, argv, "+vt:")) != -1)
    {
        switch (ret)
        {
            case 'v': 
                v_flag = 1;
                break;
            case 't':
                if (optarg == NULL) {
                    printf("Brak argumentu dla opcji -t\n");
                    return EXIT_FAILURE;
                } 
                t = atoi(optarg);
                if (t <= 0) {
                    perror("Wartosc t musi byc wieksza od 0.\n");
                    return EXIT_FAILURE;
                }
                break;
            default: abort();
        }
    }
 
    if(optind >= argc)
    {
        fprintf (stderr, "Nie podano nazwy programu testowego\n"); 
        return EXIT_FAILURE;
    }
 
    char *program = argv[optind];
    int num_args = argc - optind;
    char *arguments[num_args + 1];
    
 	arguments[0] = program;
    for (int i = 1; i <= num_args; i++) {
        arguments[i] = argv[optind + i];
    }
    arguments[num_args + 1] = NULL;
    printf("argc: %d\n", argc);
    printf("optind: %d\n\n", optind);
    
    printf("0: %s\n", arguments[0]);
    printf("1: %s\n", arguments[1]);
    printf("2: %s\n\n", arguments[2]);
 
    struct timespec start, end;
    struct rusage usage;
    double real_avg = 0, user_avg = 0, system_avg = 0;
 
    for (int i = 0; i < t; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork fail");
            return EXIT_FAILURE;
        }
        else if (pid == 0) // Child process
        {
            if (v_flag == 0)
            {
                close(1);
                int h = open("/dev/null", O_WRONLY);
                dup2(h, 1);
            }
 
            execvp(program, arguments);
            return EXIT_FAILURE;
        }
        else // Parent process
        {
            clock_gettime(CLOCK_MONOTONIC, &start);
            wait4(pid, NULL, 0, &usage);
            clock_gettime(CLOCK_MONOTONIC, &end);
 
            double real_time = (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_nsec - start.tv_nsec) / 1e6;
            double user_time = usage.ru_utime.tv_sec * 1e3 + usage.ru_utime.tv_usec / 1e3;
            double system_time = usage.ru_stime.tv_sec * 1e3 + usage.ru_stime.tv_usec / 1e3;
 
            real_avg += real_time;
            user_avg += user_time;
            system_avg += system_time;
 
            printf("Iteration %d:\n", i + 1);
            printf("Real: %.3lf ms\n", real_time);
            printf("User: %.3lf ms \n", user_time);
            printf("System: %.3lf ms \n\n", system_time);
        }
    }
 
    if (t > 1) 
    {
        printf("Average:\n");
        printf("Real: %.3lf ms \n", real_avg / t);
        printf("User: %.3lf ms \n", user_avg / t);
        printf("System: %.3lf ms \n", system_avg / t);
    }
    return EXIT_SUCCESS;
}
