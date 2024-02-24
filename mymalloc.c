#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMLENGTH 512
#define ROUNDUPTOEIGHT(n) (((n) + 7) & ~7)

static double memory[MEMLENGTH];

#define heap (char *) memory

// Define the macros for accessing block information

// Declare the coalesce function
void coalesceFreeBlocks();

// Metadata for memory block
typedef struct Header
{
    size_t size;
    int alloced;
    struct Header *next;
}Header;

// Initialize Heap
Header *heapStart = NULL;

// mymalloc function
void *mymalloc(size_t size, char *file, int line)
{
    // if the size is 0 or negative return
    if(size <= 0)
    {
        printf("Size cannot be 0 or less...");
        return NULL;
    }
    else
    {

        // Round the size up to the nearest multiple of 8
        int rounded_size = ROUNDUPTOEIGHT(size);
        // If the heap is not initialized, initialize it with the first block
        if (heapStart == NULL) 
        {
            heapStart = (Header *)heap;
            heapStart->size = rounded_size;
            heapStart->alloced = 1;
            heapStart->next = NULL;
            return (void *)(heapStart + 1);  // Return a pointer to the memory after the Block structure
            printf("Rounded size to %d in order to add additional space to memory\n", rounded_size);
            printf("Heap current size: %zu Bytes\n", heapStart->size);
        }
        

        Header *current = heapStart;
        while (current != NULL)
        {
            if (!current->alloced && current->size >= rounded_size)
            {
                // Allocate memory from the current block
                current->alloced = 1;

                // If there's extra space, split the block
                if (current->size > rounded_size + sizeof(Header))
                {
                    Header *newBlock = (Header *)((char *)current + sizeof(Header) + rounded_size);
                    newBlock->size = current->size - sizeof(Header) - rounded_size;
                    newBlock->alloced = 0;
                    newBlock->next = current->next;
                    current->next = newBlock;
                    current->size = rounded_size;
                }

                return (void *)(current + 1); // Return a pointer to the memory after the Block structure
            }
            current = current->next;
        }

        // Return NULL if there's not enough space available
        printf("Not enough space in memory...\n");
        return NULL;
    }
}

void myfree(void *ptr, char *file, int line)
{
    if (ptr == NULL) 
    {
        return;
    }

    Header *block = (Header *)((char *)ptr - sizeof(Header));
    block->alloced = 0;

    printf("Freed\n");

    // Check if the next block is also freed
        coalesceFreeBlocks();

}

void coalesceFreeBlocks()
{
    printf("Coallescing free blocks...\n");
    Header *current = heapStart;
    Header *previous = NULL;

    while (current != NULL)
    {
        if (!current->alloced && current->next != NULL && !current->next->alloced)
        {
            // Merge current block with the next block
            current->size += sizeof(Header) + current->next->size;
            current->next = current->next->next;
        }
        
        // Move to the next block
        previous = current;
        current = current->next;
    }

    // Adjust heapStart if the first block is freed and merged with the next block
    if (heapStart != NULL && !heapStart->alloced)
    {
        heapStart = heapStart->next;
    }
}





