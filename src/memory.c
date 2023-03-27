#include "memory.h"
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>

void* zmalloc(uint64_t length) {
#ifdef PRINT_ALLOC
  fprintf(stderr, "zmalloc(%lu) = ", length);
#endif
  void* ptr = malloc(length);
#ifdef PRINT_ALLOC
  fprintf(stderr, "%p\n", ptr);
#endif
  return ptr;
}

void zfree(void* location) {
#ifdef PRINT_ALLOC
  fprintf(stderr, "zfree(%p)\n", location);
#endif
  free(location);
}

void* zcalloc(uint64_t length) {
#ifdef PRINT_ALLOC
  fprintf(stderr, "zcalloc(%lu) = ", length);
#endif
  void* ptr = calloc(length, 1);
#ifdef PRINT_ALLOC
  fprintf(stderr, "%p\n", ptr);
#endif
  return ptr;
}

void* zrealloc(void* location, uint64_t length) {
#ifdef PRINT_ALLOC
  fprintf(stderr, "zrealloc(%p, %lu) = ", location, length);
#endif
  void* ptr = realloc(location, length);
#ifdef PRINT_ALLOC
  fprintf(stderr, "%p\n", ptr);
#endif
  return ptr;
}