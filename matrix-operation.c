#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int** mtxMul(int** c, int (*a)[4], int (*b)[4], int n) {
    omp_set_num_threads(2);
    #pragma omp parallel for
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                *(*(c + i) + j) = 0;
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
    // int n = 48;
    // double a[n];
    // for(int i = 0; i < n; i++) {
    //     a[i] = i + i / 10.0;
    // }
    // double *b = a;
    // double *c = b;
    // c = vectAdd(c, a, b, n);
    // for(int i = 0; i < n; i++) {
    //     printf("%.2lf\t", c[i]);
    // }

    // int max = 6;
    // omp_set_num_threads(2);
    // omp_set_nested(1);
    // #pragma omp parallel for 
    //     for(int i = 1; i <= max; i++) {
    //         #pragma omp parallel for 
    //         for(int j = 1; j <= max; j++) {
    //             printf("%d: (%d, %d)\n", omp_get_thread_num(), i, j);
    //         }
    //     }
    int a[][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
    int b[][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
    int** c;
    c = malloc(sizeof(int*) * 4);
    for(int i = 0; i < 4; i++) {
        c[i] = malloc(sizeof(int*) * 4);
    }
    int n = 4;
    // printf(a);
    mtxMul(c, a, b, n);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%d ", c[i][j]);
        }
    }
    return 0;
}