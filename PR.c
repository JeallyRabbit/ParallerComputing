#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define NUM 30000000

int isprime(int x) {
    for (int y = 2; y * y <= x; y++) {
        if (x % y == 0)
            return 0;
    }

    return 1;
}

int sitoEratostenesaSekwencyjnie(bool primes[]) {
    int primes_num = 0;
    // 0 i 1 nie są liczbami pierwszymi
    primes[0] = primes[1] = false;

    for (int i = 2; i * i < NUM; ++i) {
        // Jeśli i jest liczbą pierwszą, oznacz wszystkie jej wielokrotności jako liczby złożone
        if (primes[i]) {
            for (int j = i * i; j < NUM; j += i) {
                primes[j] = false;
            }
        }
    }

    for (int i = 0; i < NUM; i++) {
        if (primes[i]) {
            primes_num++;
        }
    }

    return primes_num;
}

int sitoEratostenesaRownolegle(bool primes[]) {
    int primes_num = 0;
    // 0 i 1 nie są liczbami pierwszymi
    primes[0] = primes[1] = false;
    int NUM_root=sqrt(NUM);
    #pragma omp parallel
    {
        //#pragma omp for
        #pragma omp for schedule(dynamic,1)//reduction(+:primes_num)
        for (int i = 2; i < NUM_root; ++i) {
            int isquare = i * i;  // Introduce a separate variable
            // Jeśli i jest liczbą pierwszą, oznacz wszystkie jej wielokrotności jako liczby złożone
            //#pragma omp critical
            {
                if (primes[i]) {
                for (int j = isquare; j < NUM; j += i) {
                    primes[j] = false;
                }
                //#pragma omp atomic
                //primes_num++;
                }
            }
            
            
        }

        #pragma omp for reduction(+:primes_num)
        for (int i = 0; i < NUM; ++i) {
            if (primes[i]) {
                primes_num++;
            }
        }
    }

    return primes_num;
}

int main(int argc, char *argv[]) {
    int sum = 0;
    double czas_start, czas_koniec;

    // SEKWENCYJNIE
    czas_start = omp_get_wtime();
    for (int i = 2; i <= NUM; i++) {
        sum += isprime(i);
    }
    czas_koniec = omp_get_wtime();
    printf("Number of primes numbers: %d\n", sum);
    printf("Czas przetwarzania sekwencyjnego: %f seconds\n", czas_koniec - czas_start);

    // RÓWNOLEGLE
    sum = 0;
    czas_start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for (int i = 2; i < NUM; i++) {
        sum += isprime(i);
    }
    czas_koniec = omp_get_wtime();
    printf("Number of primes numbers: %d\n", sum);
    printf("Czas przetwarzania równoległego: %f seconds\n", czas_koniec - czas_start);
    printf("Liczba watkow: %d\n", omp_get_num_threads());

    // SITO ERATOSTENESA SEKWENCYJNIE
    
    //bool primes[NUM];
    bool* primes;
    primes=(bool*)malloc(NUM*sizeof(bool));
    for (int i = 0; i < NUM; ++i) {
        primes[i] = true;
    }
    
    czas_start = omp_get_wtime();
    printf("Number of primes numbers with sieve: %d\n", sitoEratostenesaSekwencyjnie(primes));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania sekwencyjnego sita Eratostenesa: %f seconds\n", czas_koniec - czas_start);
    
    
    

//SITO ERATOSTENESA ROWNOLEGLE
    for (int i = 0; i < NUM; ++i) {
            primes[i] = true;
    }
    czas_start = omp_get_wtime();
    printf("Number of primes numbers with sieve: %d\n", sitoEratostenesaRownolegle(primes));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego sita Eratostenesa: %f seconds\n", czas_koniec - czas_start);
    printf("Liczba watkow: %d\n", omp_get_num_threads());

    
    return 0;
}
