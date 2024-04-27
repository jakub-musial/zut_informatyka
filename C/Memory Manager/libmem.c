#include "libmem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MemoryBlock {
    void *ptr;
    size_t size;
    struct MemoryBlock *next;
} MemoryBlock;

MemoryBlock *list_head = NULL;

int mem_errno = 0;

void cleanup_memory()
{
    MemoryBlock *current_block = list_head;
    while (current_block != NULL) {
        MemoryBlock *next_block = current_block->next;
        free(current_block->ptr);
        free(current_block);
        current_block = next_block;
    }
}

void *mem_alloc(void *ptr, unsigned int size)
{
    if (ptr == NULL)
    {
        MemoryBlock *new_block = malloc(sizeof(MemoryBlock));

        void *new_ptr = calloc(1, size);
        if (new_ptr == NULL) {
            mem_errno = -1;
            return NULL;
        }

        new_block->ptr = new_ptr;
        new_block->size = size;
        new_block->next = list_head;
        list_head = new_block;
        return new_block->ptr;
    }
    else
    {
        MemoryBlock *current_block = list_head;
        while (current_block->ptr != NULL)
        {
            if (current_block == ptr && current_block->size != size)
            {
                void *new_ptr = realloc(current_block->ptr, size);
                if (new_ptr == NULL) {
                    mem_errno = -2;
                    return NULL;
                }

                current_block->ptr = new_ptr;
                current_block->size = size;
                return current_block->ptr;
            }
            current_block = current_block->next;
        }
    }
    return NULL;
}

int mem_free(void *ptr)
{
    MemoryBlock *previous_block = NULL;
    MemoryBlock *current_block = list_head;
    while (current_block != NULL)
    {
        if (current_block->ptr == ptr)
        {
            if (previous_block != NULL) {
                previous_block->next = current_block->next;
            }

            free(current_block->ptr);
            free(current_block);
            return 0;
        }
        previous_block = current_block;
        current_block = current_block->next;
    }   
    mem_errno = -3;
    return -1;
}

__attribute__((constructor))
void initialize_memory_manager() {
    atexit(cleanup_memory);
}
