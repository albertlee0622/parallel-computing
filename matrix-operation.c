#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int** mtxMul(int** c, int** a, int** b, int n) {
    omp_set_num_threads(2);
    #pragma omp parallel for
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                c[i][j] = 0;
                for(int k = 0; k < n; k++) {
                    c[i][j] = c[i][j] + a[i][k] * b[k][j];
                }
            }
            printf("(%d: row %d) ", omp_get_thread_num(), i);

        }
    return c;
}

double *vectAdd(double *c, double *a, double *b, int n) {
    #pragma omp parallel for
        for(int i = 0; i < n; i++) {
            c[i] = a[i] + b[i];
            printf("%d: (%d, %.1lf)", omp_get_thread_num(), i, c[i]);
            printf("\n");
        }
    return c;
}

int main(int argc, char* argv[]) {

    int **a, **b, **c;
    int n = 10;
    
    n = atoi(argv[1]);
    a = malloc(sizeof(int*) * n);
    b = malloc(sizeof(int*) * n);
    c = malloc(sizeof(int*) * n);

    for(int i = 0; i < n; i++) {
        a[i] = malloc(sizeof(int*) * n);
        b[i] = malloc(sizeof(int*) * n);
        c[i] = malloc(sizeof(int*) * n);
    }

    int k = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            k++;
            a[i][j] = k;
            b[i][j] = k;
        }
    }

    mtxMul(c, a, b, n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", c[i][j]);
        }
    }

    return 0;
}