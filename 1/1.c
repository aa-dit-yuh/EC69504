#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    int lambda = 4;             // Average arrival rate
    int N = 1000;               // Number of arrivals
    double E[N];                // Arrival time for nth packet
    int slotCount = 4*lambda;   // Number of slot in histogram
    int arrivals[N/4];
    int P[slotCount];           // Stores histogram of number of arrivals

    int i;
    E[0] = 0;
    for (i = 0; i < N; i++) arrivals[i] = 0;
    for (i = 0; i < slotCount; i++) P[i] = 0;

    time_t t;
    srand((unsigned) time(&t));

    for(i = 1; i < N; i++) {
        double U = (float)rand()/RAND_MAX;
        double e = -log(U)/lambda;
        E[i] = E[i-1] + e;
        arrivals[(int)(E[i]/4)]++;
    }
    
    for (i = 0; i < N; i++) {
        if (arrivals[i]/4 < slotCount)
            P[arrivals[i]/4]++;
    }
    FILE *f = fopen("data.csv", "w");
    fprintf(f, "0, 0\n");
    printf("P[0] = 0\n");
    for (i = 1; i < slotCount; i++) {
        fprintf(f, "%d, %d\n", i , P[i]);
        printf("P[%d] = %d\n", i, P[i]);
    }
    fclose(f);
    return 0; 
}
