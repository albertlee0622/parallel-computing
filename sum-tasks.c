#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int max; sscanf(argv[1], "%d", &max);
    int tasks; sscanf(argv[2], "%d", &tasks);
    if(max % tasks != 0) return 1;
    int sum = 0;
    omp_set_num_threads(5);
    #pragma omp parallel
    {
        #pragma omp single
        for(int t = 0; t < tasks; t++) {
            #pragma omp task
            {
                int h = max / tasks;
                int local_sum = 0;
                int lo = h * t + 1;
                int hi = h * (t + 1);
                for(int i = lo; i <= hi; i++)
                {
                    local_sum = local_sum + i;
                    printf("%d: add %d then %d | ", omp_get_thread_num(), i, local_sum);
                }
                #pragma omp atomic
                    sum = sum + local_sum;
            }
        }
    }
    printf("%d\n", sum);
}