#include <iostream>
#include <omp.h>

#define DATA_SIZE 50000

void sort_data(int* data) {
    for (int i = 0; i < DATA_SIZE; i++) {
        for (int j = 0; j < DATA_SIZE - 1; j++) {
            if (data[j] > data[j + 1]) {
                int help = data[j];
                data[j] = data[j + 1];
                data[j + 1] = help;
            }
        }
    }
}

void sort_data_parallelized(int* data) {
#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < DATA_SIZE; i++) {
        for (int j = 0; j < DATA_SIZE - 1; j++) {
            if (data[j] > data[j + 1]) {
                int help = data[j];
                data[j] = data[j + 1];
                data[j + 1] = help;
            }
        }
    }
}

void sort_data_mod(int* data) { //TODO Optimize the sorting algorithm further by using modulo %
#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < DATA_SIZE; i++) {
        for (int j = 0; j < DATA_SIZE - 1; j++) {
            if (data[j] > data[j + 1]) {
                int help = data[j];
                data[j] = data[j + 1];
                data[j + 1] = help;
            }
        }
    }
}

void randomizeData(int* data) {
    for (int i = 0; i < DATA_SIZE; ++i) {
        data[i] = std::rand();
    }
    printf("Before sorting: ");
    for (int i  = DATA_SIZE - 1; i >= DATA_SIZE - 10; i--) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

void printData(int* data) {
    printf("After sorting: ");
    for (int i  = DATA_SIZE - 1; i >= DATA_SIZE - 10; i--) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int main() {
    std::srand(time(nullptr));
    double startTime, endTime;

    int data[DATA_SIZE];

    //=================================================================
    //Single Thread
    printf("\nRunning on single thread\n");
    randomizeData(data);
    startTime = omp_get_wtime();
    sort_data(data);
    endTime = omp_get_wtime();
    printf("Time taken: %f\n", endTime - startTime);
    printData(data);
    //=================================================================

    //=================================================================
    //Parallelized
    printf("\nRunning on parallel version\n");
    randomizeData(data);
    startTime = omp_get_wtime();
    sort_data_parallelized(data);
    endTime = omp_get_wtime();
    printf("Time taken: %f\n", endTime - startTime);
    printData(data);
    //=================================================================

    //=================================================================
    //Optimize the sorting algorithm further by using modulo %.
    printf("\nRunning on optimized version\n");
    randomizeData(data);
    startTime = omp_get_wtime();
    sort_data_mod(data);
    endTime = omp_get_wtime();
    printf("Time taken: %f\n", endTime - startTime);
    printData(data);
    //=================================================================

    return 0;
}
