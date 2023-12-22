#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define MIN 2
#define NUM 10000000 // 10mln
//dla 10000 jest 1229 liczb pierwszych
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

/*int sitoEratostenesaRownolegle(bool primes[]) {
    int primes_num = 0;
    // 0 i 1 nie są liczbami pierwszymi
    primes[0] = primes[1] = false;
    int NUM_root=sqrt(NUM);
    #pragma omp parallel
    {
        //#pragma omp for
        //omp_set_num_threads(2);
        #pragma omp for schedule(dynamic,1)//reduction(+:primes_num)
        for (int i = 2; i <= NUM_root; ++i) {
            int isquare = i * i;  // Introduce a separate variable
            // Jeśli i jest liczbą pierwszą, oznacz wszystkie jej wielokrotności jako liczby złożone
            //#pragma omp critical
            {
                if (primes[i]) {
                for (int j = isquare; j < NUM; j += i) {
                    primes[j] = false;
                }
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
*/



void oznacz_nie_pierwsze_for_schedule_static_1(bool primes[], int n, int start, int end) {
    #pragma omp parallel for schedule (static,1)
    for (int i = start; i < end; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            for (int j = i * 2; j < n; j += i) {
                primes[j] = false;
            }
        }
    }
}

int sitoFunkcyjnie_for_schedule_static_1(bool primes[], int n) {
    
    primes[0] = primes[1] = false;
    // Use task parallelism to mark non-prime numbers
    for (int i = 2; i * i < n; ++i) {
        if (primes[i]) {
            oznacz_nie_pierwsze_for_schedule_static_1(primes, n, i , n);
        }
    }
    int primes_num=0;
    #pragma omp parallel//reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
        }
    }
    return primes_num;
}

void oznacz_nie_pierwsze_for_schedule_static_2(bool primes[], int n, int start, int end) {
    #pragma omp parallel for schedule (static,2)
    for (int i = start; i < end; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            for (int j = i * 2; j < n; j += i) {
                primes[j] = false;
            }
        }
    }
}

int sitoFunkcyjnie_for_schedule_static_2(bool primes[], int n) {
    
    primes[0] = primes[1] = false;
    // Use task parallelism to mark non-prime numbers
    for (int i = 2; i * i < n; ++i) {
        if (primes[i]) {
            oznacz_nie_pierwsze_for_schedule_static_2(primes, n, i , n);
        }
    }
    int primes_num=0;
    #pragma omp parallel//reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
        }
    }
    return primes_num;
}

void oznacz_nie_pierwsze_for_schedule_static_4(bool primes[], int n, int start, int end) {
    #pragma omp parallel for schedule (static,4)
    for (int i = start; i < end; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            for (int j = i * 2; j < n; j += i) {
                primes[j] = false;
            }
        }
    }
}

int sitoFunkcyjnie_for_schedule_static_4(bool primes[], int n) {
    
    primes[0] = primes[1] = false;
    // Use task parallelism to mark non-prime numbers
    for (int i = 2; i * i < n; ++i) {
        if (primes[i]) {
            oznacz_nie_pierwsze_for_schedule_static_4(primes, n, i , n);
        }
    }
    int primes_num=0;
    #pragma omp parallel//reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
        }
    }
    return primes_num;
}

void oznacz_nie_pierwsze_for_schedule_static_8(bool primes[], int n, int start, int end) {
    #pragma omp parallel for schedule (static,8)
    for (int i = start; i < end; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            for (int j = i * 2; j < n; j += i) {
                primes[j] = false;
            }
        }
    }
}

int sitoFunkcyjnie_for_schedule_static_8(bool primes[], int n) {
    
    primes[0] = primes[1] = false;
    // Use task parallelism to mark non-prime numbers
    for (int i = 2; i * i < n; ++i) {
        if (primes[i]) {
            oznacz_nie_pierwsze_for_schedule_static_8(primes, n, i , n);
        }
    }
    int primes_num=0;
    #pragma omp parallel//reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
        }
    }
    return primes_num;
}

void oznacz_nie_pierwsze_for_schedule_dynamic_1(bool primes[], int n, int start, int end) {
    #pragma omp parallel for schedule (dynamic,1)
    for (int i = start; i < end; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            for (int j = i * 2; j < n; j += i) {
                primes[j] = false;
            }
        }
    }
}

int sitoFunkcyjnie_for_schedule_dynamic_1(bool primes[], int n) {
    
    primes[0] = primes[1] = false;
    // Use task parallelism to mark non-prime numbers
    for (int i = 2; i * i < n; ++i) {
        if (primes[i]) {
            oznacz_nie_pierwsze_for_schedule_dynamic_1(primes, n, i , n);
        }
    }
    int primes_num=0;
    #pragma omp parallel//reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
        }
    }
    return primes_num;
}

void oznacz_nie_pierwsze_for_schedule_dynamic_2(bool primes[], int n, int start, int end) {
    #pragma omp parallel for schedule (dynamic,2)
    for (int i = start; i < end; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            for (int j = i * 2; j < n; j += i) {
                primes[j] = false;
            }
        }
    }
}

int sitoFunkcyjnie_for_schedule_dynamic_2(bool primes[], int n) {
    
    primes[0] = primes[1] = false;
    // Use task parallelism to mark non-prime numbers
    for (int i = 2; i * i < n; ++i) {
        if (primes[i]) {
            oznacz_nie_pierwsze_for_schedule_dynamic_2(primes, n, i , n);
        }
    }
    int primes_num=0;
    #pragma omp parallel//reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
        }
    }
    return primes_num;
}


void oznacz_nie_pierwsze_for_schedule_dynamic_4(bool primes[], int n, int start, int end) {
    #pragma omp parallel for schedule (dynamic,4)
    for (int i = start; i < end; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            for (int j = i * 2; j < n; j += i) {
                primes[j] = false;
            }
        }
    }
}

int sitoFunkcyjnie_for_schedule_dynamic_4(bool primes[], int n) {
    
    primes[0] = primes[1] = false;
    // Use task parallelism to mark non-prime numbers
    for (int i = 2; i * i < n; ++i) {
        if (primes[i]) {
            oznacz_nie_pierwsze_for_schedule_dynamic_4(primes, n, i , n);
        }
    }
    int primes_num=0;
    #pragma omp parallel//reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
        }
    }
    return primes_num;
}

void oznacz_nie_pierwsze_for_schedule_dynamic_8(bool primes[], int n, int start, int end) {
    #pragma omp parallel for schedule (dynamic,8)
    for (int i = start; i < end; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            for (int j = i * 2; j < n; j += i) {
                primes[j] = false;
            }
        }
    }
}

int sitoFunkcyjnie_for_schedule_dynamic_8(bool primes[], int n) {
    
    primes[0] = primes[1] = false;
    // Use task parallelism to mark non-prime numbers
    for (int i = 2; i * i < n; ++i) {
        if (primes[i]) {
            oznacz_nie_pierwsze_for_schedule_dynamic_8(primes, n, i , n);
        }
    }
    int primes_num=0;
    #pragma omp parallel//reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
        }
    }
    return primes_num;
}


int sitoDomenowo_for_schedule_static_1(bool primes[], int n) {
    

    primes[0] = primes[1] = false;
    // Use data parallelism to mark non-prime numbers
    int NUM_root=sqrt(NUM);
    #pragma omp parallel for schedule (static,1)
    for (int i = 2; i <= NUM_root; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            #pragma omp parallel for
            for (int j = i * 2; j <= n; j += i) {
                primes[j] = false;
            }
        }
    }

    int primes_num=0;
    #pragma omp parallel //reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
    }
    }
    return primes_num;
}

int sitoDomenowo_for_schedule_static_2(bool primes[], int n) {
    

    primes[0] = primes[1] = false;
    // Use data parallelism to mark non-prime numbers
    int NUM_root=sqrt(NUM);
    #pragma omp parallel for schedule (static,2)
    for (int i = 2; i <= NUM_root; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            #pragma omp parallel for
            for (int j = i * 2; j <= n; j += i) {
                primes[j] = false;
            }
        }
    }

    int primes_num=0;
    #pragma omp parallel //reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
    }
    }
    return primes_num;
}

int sitoDomenowo_for_schedule_static_4(bool primes[], int n) {
    

    primes[0] = primes[1] = false;
    // Use data parallelism to mark non-prime numbers
    int NUM_root=sqrt(NUM);
    #pragma omp parallel for schedule (static,4)
    for (int i = 2; i <= NUM_root; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            #pragma omp parallel for
            for (int j = i * 2; j <= n; j += i) {
                primes[j] = false;
            }
        }
    }

    int primes_num=0;
    #pragma omp parallel //reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
    }
    }
    return primes_num;
}

int sitoDomenowo_for_schedule_static_8(bool primes[], int n) {
    

    primes[0] = primes[1] = false;
    // Use data parallelism to mark non-prime numbers
    int NUM_root=sqrt(NUM);
    #pragma omp parallel for schedule (static,8)
    for (int i = 2; i <= NUM_root; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            #pragma omp parallel for
            for (int j = i * 2; j <= n; j += i) {
                primes[j] = false;
            }
        }
    }

    int primes_num=0;
    #pragma omp parallel //reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
    }
    }
    return primes_num;
}


int sitoDomenowo_for_schedule_dynamic_1(bool primes[], int n) {
    

    primes[0] = primes[1] = false;
    // Use data parallelism to mark non-prime numbers
    int NUM_root=sqrt(NUM);
    #pragma omp parallel for schedule (dynamic,1)
    for (int i = 2; i <= NUM_root; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            #pragma omp parallel for
            for (int j = i * 2; j <= n; j += i) {
                primes[j] = false;
            }
        }
    }

    int primes_num=0;
    #pragma omp parallel //reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
    }
    }
    return primes_num;
}

int sitoDomenowo_for_schedule_dynamic_2(bool primes[], int n) {
    

    primes[0] = primes[1] = false;
    // Use data parallelism to mark non-prime numbers
    int NUM_root=sqrt(NUM);
    #pragma omp parallel for schedule (dynamic,2)
    for (int i = 2; i <= NUM_root; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            #pragma omp parallel for
            for (int j = i * 2; j <= n; j += i) {
                primes[j] = false;
            }
        }
    }

    int primes_num=0;
    #pragma omp parallel //reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
    }
    }
    return primes_num;
}

int sitoDomenowo_for_schedule_dynamic_4(bool primes[], int n) {
    

    primes[0] = primes[1] = false;
    // Use data parallelism to mark non-prime numbers
    int NUM_root=sqrt(NUM);
    #pragma omp parallel for schedule (dynamic,4)
    for (int i = 2; i <= NUM_root; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            #pragma omp parallel for
            for (int j = i * 2; j <= n; j += i) {
                primes[j] = false;
            }
        }
    }

    int primes_num=0;
    #pragma omp parallel //reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
            primes_num++;
        }
    }
    }
    return primes_num;
}

int sitoDomenowo_for_schedule_dynamic_8(bool primes[], int n) {
    

    primes[0] = primes[1] = false;
    // Use data parallelism to mark non-prime numbers
    int NUM_root=sqrt(NUM);
    #pragma omp parallel for schedule (dynamic,8)
    for (int i = 2; i <= NUM_root; ++i) {
        if (primes[i]) {
            // Mark multiples of the current prime number as non-prime
            #pragma omp parallel for
            for (int j = i * 2; j <= n; j += i) {
                primes[j] = false;
            }
        }
    }

    int primes_num=0;
    #pragma omp parallel //reduction(+:primes_num)
    {
        for (int i = 0; i < NUM; ++i) {
        if(primes[i] == true)
        {
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
    printf("Czas przetwarzania sekwencyjnego: %f seconds\n\n", czas_koniec - czas_start);

    // RÓWNOLEGLE
    sum = 0;
    czas_start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for (int i = 2; i < NUM; i++) {
        sum += isprime(i);
    }
    czas_koniec = omp_get_wtime();
    printf("Number of primes numbers: %d\n", sum);
    printf("Czas przetwarzania równoległego: %f seconds\n\n", czas_koniec - czas_start);

    bool* primes;
    primes=(bool*)malloc(NUM*sizeof(bool));
    for (int i = 0; i < NUM; ++i) {
        primes[i] = true;
    }
    
    czas_start = omp_get_wtime();
    printf("Number of primes numbers with sieve: %d\n", sitoEratostenesaSekwencyjnie(primes));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania sekwencyjnego sita Eratostenesa: %f seconds\n\n", czas_koniec - czas_start);
    
    
    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoFunkcyjnie_for_schedule_static_1(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - FUNKCYJNIE for schedule (static,1) %f seconds\n\n", czas_koniec - czas_start);


    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoFunkcyjnie_for_schedule_static_2(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - FUNKCYJNIE for schedule (static,2) %f seconds\n\n", czas_koniec - czas_start);


    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoFunkcyjnie_for_schedule_static_4(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - FUNKCYJNIE for schedule (static,4) %f seconds\n\n", czas_koniec - czas_start);

    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoFunkcyjnie_for_schedule_static_8(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - FUNKCYJNIE for schedule (static,8) %f seconds\n\n", czas_koniec - czas_start);


    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoFunkcyjnie_for_schedule_dynamic_1(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - FUNKCYJNIE for schedule (dynamic,1) %f seconds\n\n", czas_koniec - czas_start);

    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoFunkcyjnie_for_schedule_dynamic_2(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - FUNKCYJNIE for schedule (dynamic,2) %f seconds\n\n", czas_koniec - czas_start);


    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoFunkcyjnie_for_schedule_dynamic_4(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - FUNKCYJNIE for schedule (dynamic,4) %f seconds\n\n", czas_koniec - czas_start);

    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoFunkcyjnie_for_schedule_dynamic_8(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - FUNKCYJNIE for schedule (dynamic,8) %f seconds\n\n", czas_koniec - czas_start);


    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoDomenowo_for_schedule_static_1(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - sitoDomenowo for schedule (static,1) %f seconds\n\n", czas_koniec - czas_start);

    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoDomenowo_for_schedule_static_2(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - sitoDomenowo for schedule (static,2) %f seconds\n\n", czas_koniec - czas_start);

    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoDomenowo_for_schedule_static_4(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - sitoDomenowo for schedule (static,4) %f seconds\n\n", czas_koniec - czas_start);

    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoDomenowo_for_schedule_static_8(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - sitoDomenowo for schedule (static,8) %f seconds\n\n", czas_koniec - czas_start);


    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoDomenowo_for_schedule_dynamic_1(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - sitoDomenowo for schedule (dynamic,1) %f seconds\n\n", czas_koniec - czas_start);

    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoDomenowo_for_schedule_dynamic_2(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - sitoDomenowo for schedule (dynamic,2) %f seconds\n\n", czas_koniec - czas_start);

    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoDomenowo_for_schedule_dynamic_4(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - sitoDomenowo for schedule (dynamic,4) %f seconds\n\n", czas_koniec - czas_start);

    for(int i=0;i<NUM;++i){
        primes[i]=true;
    }
    czas_start=omp_get_wtime();
    printf("Licba pierwszych: %d\n", sitoDomenowo_for_schedule_dynamic_8(primes,NUM));
    czas_koniec = omp_get_wtime();
    printf("Czas przetwarzania rownoleglego - sitoDomenowo for schedule (dynamic,8) %f seconds\n\n", czas_koniec - czas_start);

    /*for (int i = 0; i < NUM; ++i) {
            if(primes[i]==true)
            {
                printf("%d ",i);
            }
    }
    printf("\n");*/
    

    return 0;
}
