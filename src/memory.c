#include "memory.h"
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef PRINT_ALLOC
void* zmalloc(uint64_t length) {
  return malloc(length);
}
#else
void* zmalloc(uint64_t length, const char* file, int line) {
  fprintf(stderr, "%s:%d zmalloc(%lu) = ", file, line, length);
  void* ptr = malloc(length);
  fprintf(stderr, "%p\n", ptr);
  return ptr;
}
#endif

#ifndef PRINT_ALLOC
void zfree(void* location) {
  free(location);
}
#else
void zfree(void* location, const char* file, int line) {
  fprintf(stderr, "%s:%d zfree(%p)\n", file, line, location);
  free(location);
}
#endif

#ifndef PRINT_ALLOC
void* zcalloc(uint64_t length) {
  return calloc(length, 1);
}
#else
void* zcalloc(uint64_t length, const char* file, int line) {
  fprintf(stderr, "%s:%d zcalloc(%lu) = ", file, line, length);
  void* ptr = calloc(length, 1);
  fprintf(stderr, "%p\n", ptr);
  return ptr;
}
#endif


#ifndef PRINT_ALLOC
void* zrealloc(void* location, uint64_t length) {
  return realloc(location, length);
}
#else
void* zrealloc(void* location, uint64_t length, const char* file, int line) {
  fprintf(stderr, "%s:%d zrealloc(%p, %lu) = ", file, line, location, length);
  void* ptr = realloc(location, length);
  fprintf(stderr, "%p\n", ptr);
  return ptr;
}
#endif