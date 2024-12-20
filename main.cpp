//
//  WARNING: THIS CODE DOES NOT WORK PROPERLY, DO NOT USE IT
//

#include <iostream>
#include <omp.h>

#define DATA_SIZE 50000

void sort_data(int *data, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (data[j] > data[j + 1]) {
                int help = data[j];
                data[j] = data[j + 1];
                data[j + 1] = help;
            }
        }
    }
}

void sort_data_parallelized(int *data) {
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

void sort_data_mod(int *data) {
    // Separate odd and even numbers by using modulo
    int oddNumbers[DATA_SIZE], evenNumbers[DATA_SIZE];
    int oddCount = 0, evenCount = 0;

    for (int i = 0; i < DATA_SIZE; i++) {
        if (data[i] % 2 == 0) {
            evenNumbers[evenCount] = data[i];
            evenCount++;
        } else {
            oddNumbers[oddCount] = data[i];
            oddCount++;
        }
    }

    sort_data(oddNumbers, oddCount);
    sort_data(evenNumbers, evenCount);

    /*
    for (int i = 0; i < oddCount; i++) {
        for (int j = 0; j < oddCount - 1; j++) {
            if (oddNumbers[j] > oddNumbers[j + 1]) {
                int temp = oddNumbers[j];
                oddNumbers[j] = oddNumbers[j + 1];
                oddNumbers[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < evenCount; i++) {
        for (int j = 0; j < evenCount - 1; j++) {
            if (evenNumbers[j] > evenNumbers[j + 1]) {
                int temp = evenNumbers[j];
                evenNumbers[j] = evenNumbers[j + 1];
                evenNumbers[j + 1] = temp;
            }
        }
    }
    */

    int j = 0;
    int e = 0;
    int o = 0;
    while (j < DATA_SIZE) {
        if (oddNumbers[o] > evenNumbers[e]) {
            data[j++] = oddNumbers[o++];
        }
        else {
            data[j++] = evenNumbers[e++];
        }
    }
}

void randomizeData(int *data) {
    for (int i = 0; i < DATA_SIZE; ++i) {
        data[i] = std::rand();
    }
    printf("Before sorting: ");
    for (int i = DATA_SIZE - 1; i >= DATA_SIZE - 10; i--) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

void printData(int *data) {
    printf("After sorting: ");
    for (int i = DATA_SIZE - 1; i >= DATA_SIZE - 10; i--) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

// Experimental :)
void shuffle(int *arr, int size);

bool isSorted(int *arr, int size);

void bogoSort(int *data);

int main() {
    std::srand(time(nullptr));
    double startTime, endTime;

    int data[DATA_SIZE];

    // IDEA: run the following on separate threads


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
    //Single Thread
    printf("\nRunning on single thread\n");
    randomizeData(data);
    startTime = omp_get_wtime();
    sort_data(data, DATA_SIZE);
    endTime = omp_get_wtime();
    printf("Time taken: %f\n", endTime - startTime);
    printData(data);
    //=================================================================



    //=================================================================
    //Optimize the sorting algorithm further by using modulo %.
    printf("\nRunning on optimized version (single thread)\n");
    randomizeData(data);
    startTime = omp_get_wtime();
    sort_data_mod(data);
    endTime = omp_get_wtime();
    printf("Time taken: %f\n", endTime - startTime);
    printData(data);
    //=================================================================

    /*
    // Use at your own risk, runs more than 10 minutes sometimes :D
    //=================================================================
    //Optimize the sorting algorithm further by using modulo %.
    printf("\nRunning on bogo sort\n");
    randomizeData(data);
    startTime = omp_get_wtime();
    bogoSort(data);
    endTime = omp_get_wtime();
    printf("Time taken: %f\n", endTime - startTime);
    printData(data);
    //=================================================================
    */
    return 0;
}

void shuffle(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        int randomIndex = rand() % size;
        std::swap(arr[i], arr[randomIndex]);
    }
}

bool isSorted(int *arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

void bogoSort(int *data) {
    while (!isSorted(data, DATA_SIZE)) {
        shuffle(data, DATA_SIZE);
    }
}
