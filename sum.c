#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    int max; 
    int sum = 0;
    sscanf(argv[1], "%d", &max);

    omp_set_num_threads(5);
    #pragma omp parallel for reduction (+:sum) schedule(static, 2)
        for(int i = 1; i <= max; i++) {
                sum = sum + i;
                printf("%d: add %d then %d | ", omp_get_thread_num(), i, sum);
        }
    printf("%d\n", sum);
    return 0;
}