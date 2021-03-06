#include <stdio.h>
#include <omp.h>
#include <math.h>

int main(int argc, char* argv[]) {
    int intervals; sscanf(argv[1], "%d", &intervals);
    double integral = 0.0;
    double dx = 1.0 / intervals, x, fx;

    #pragma omp parallel for reduction(+:integral)
        for(int i = 0; i < intervals; i++) {
            x += dx;
            fx = sqrt(1.0 - x * x);
            integral = integral + fx * dx;
        }
    double pi = 4 * integral;
    printf("%20.18lf\n", pi);
    
    return 0;
}