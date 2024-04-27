#ifndef LIBMEM_H
#define LIBMEM_H

extern int mem_errno;

void *mem_alloc(void *ptr, unsigned int size);
int mem_free(void *ptr);

#endif //LIBMEM_H
