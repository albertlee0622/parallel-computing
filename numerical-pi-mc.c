#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

// double rnd(unsigned int *seed) {
//     srand(*seed);
//     return rand();
// }

int main(int argc, char *argv[]) {
    int num_shots; sscanf(argv[1], "%d", &num_shots);
    unsigned int seeds[omp_get_max_threads()];
    for(int thread = 0; thread < omp_get_max_threads(); thread++)
        seeds[thread] = thread;
    int num_hits = 0;
    unsigned int seed = omp_get_thread_num();
    #pragma omp parallel 
    {
        srand((unsigned int)omp_get_num_threads());
        #pragma omp for reduction(+:num_hits)
        for(int shot = 0; shot < num_shots; shot++) {
            
            double x = rand() / (double)RAND_MAX;
            double y = rand() / (double)RAND_MAX;;
            if(x * x + y * y <= 1) num_hits = num_hits + 1;
        }
    }
    
double pi = 4.0 * (double)num_hits / (double)num_shots;
    printf("%20.18lf\n", pi);
    return 0;
}