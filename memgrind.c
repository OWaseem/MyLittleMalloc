#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mymalloc.h"



// Function to perform the computation we want to measure
void performComputation() 
{

    for (int i = 0; i < 120; i++) {
        int *arr = (int *)mymalloc(1, "mymalloc.c", 12);
        if (arr != NULL) {
            arr[i] = i + 1;
            myfree(arr, "mymalloc.c", 131);
        }
    }
}

void performComputation2()
    {

        int *arr = (int *)mymalloc(120, "mymalloc.c", 23);
        if (arr != NULL) 
        {
            for (int i = 0; i < 120; i++) {
                arr[i] = i + 1;
            }

            printf("Array: ");
            for (int i = 0; i < 120; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");

            myfree(arr, "mymalloc.c", 131);
        }

    }

void performComputation3()
{

    srand(time(0));
    void *pointers[120] = {NULL};
    int allocated_count = 0;

    for (int i = 0; i < 120; i++) {
        int choice = rand() % 2; // Random choice: 0 for allocation, 1 for deallocation

        if (choice == 0 && allocated_count < 120) { // Allocate
            pointers[allocated_count] = malloc(1); // Allocate 1 byte
            if (pointers[allocated_count] != NULL) {
                printf("Allocated 1 byte, pointer: %p\n", pointers[allocated_count]);
                allocated_count++;
            }
        } else if (choice == 1 && allocated_count > 0) { // Deallocate
            int index = rand() % allocated_count; // Randomly choose an allocated pointer to deallocate
            free(pointers[index]);
            printf("Deallocated pointer: %p\n", pointers[index]);
            pointers[index] = pointers[allocated_count - 1];
            allocated_count--;
        }
    }

    // Deallocate any remaining allocated objects
    for (int i = 0; i < allocated_count; i++) {
        free(pointers[i]);
        printf("Deallocated pointer: %p\n", pointers[i]);
    }
}

int main(int argc, char *argv[]) {

    struct timeval start_time, end_time;
    double elapsed_time_sum = 0.0;
    double elapsed_time_sum2 = 0.0;
    double elapsed_time_sum3 = 0.0;
    int num_iterations = 50; // Number of iterations to measure
    
    // Test 1
    printf("\n\n\n");
    printf("\nTest 1: Allocate 1-byte of storage and then immediately free it 120 times\n");

    for (int i = 0; i < num_iterations; i++) {
        gettimeofday(&start_time, NULL); // Get start time

        // Perform the computation we want to measure

        performComputation();

        gettimeofday(&end_time, NULL); // Get end time

        // Calculate elapsed time in milliseconds
        double elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0; // seconds to milliseconds
        elapsed_time += (end_time.tv_usec - start_time.tv_usec) / 1000.0; // microseconds to milliseconds
        
        elapsed_time_sum += elapsed_time;
    }

    // Calculate average elapsed time
    double average_elapsed_time = elapsed_time_sum / num_iterations;
    printf("Average computing time: %.6f milliseconds\n", average_elapsed_time);

    // Test 2
    struct timeval start_time2, end_time2;

    printf("\nTest 2: Allocate 120 bits of storage and print out values 1 - 120 from my Heap\n");
    printf("\n");

    for (int i = 0; i < num_iterations; i++) {
        gettimeofday(&start_time2, NULL); // Get start time

        // Perform the computation we want to measure

        performComputation2();

        gettimeofday(&end_time2, NULL); // Get end time

        // Calculate elapsed time in milliseconds
        double elapsed_time2= (end_time2.tv_sec - start_time2.tv_sec) * 1000.0; // seconds to milliseconds
        elapsed_time2+= (end_time2.tv_usec - start_time2.tv_usec) / 1000.0; // microseconds to milliseconds
        
        elapsed_time_sum2 += elapsed_time2;
    }

    // Calculate average elapsed time
    double average_elapsed_time2 = elapsed_time_sum2 / num_iterations;
    printf("\nAverage computing time: %.6f milliseconds\n", average_elapsed_time2);

    // Test 3
    struct timeval start_time3, end_time3;

    printf("\nTest 3: Randomly allocate or free memory from an array of 120 pointers and finish when allocated 120 times\n");
    printf("\n");

    for (int i = 0; i < num_iterations; i++) {
        gettimeofday(&start_time3, NULL); // Get start time

        // Perform the computation we want to measure

        performComputation3();

        gettimeofday(&end_time3, NULL); // Get end time

        // Calculate elapsed time in milliseconds
        double elapsed_time3= (end_time3.tv_sec - start_time3.tv_sec) * 1000.0; // seconds to milliseconds
        elapsed_time3+= (end_time3.tv_usec - start_time3.tv_usec) / 1000.0; // microseconds to milliseconds
        
        elapsed_time_sum3 += elapsed_time3;
    }

    // Calculate average elapsed time
    double average_elapsed_time3 = elapsed_time_sum3 / num_iterations;
    printf("\nAverage computing time: %.6f milliseconds\n", average_elapsed_time3);
   

    return 0;
}