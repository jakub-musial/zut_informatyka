#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Użycie: %s <liczba>\n", argv[0]);
        return EXIT_FAILURE;
    }
 
    int n = atoi(argv[1]);
    if (n <= 2) {
        printf("Podana liczba musi byc wieksza od 2\n");
        return EXIT_FAILURE;
    }
 
    unsigned long long *fib = (unsigned long long*) malloc(n * sizeof(unsigned long long));
    if (fib == NULL) {
        printf("Błąd alokacji pamięci\n");
        return EXIT_FAILURE;
    }
 
    fib[0] = 1;
    fib[1] = 1;
 
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
 
    for (int i = 0; i < n; i++) {
        printf("wyraz nr %d: %llu\n", i + 1, fib[i]);
    }
 
    free(fib);
 
    return EXIT_SUCCESS;
}