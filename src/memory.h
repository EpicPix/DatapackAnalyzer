#pragma once

#include <stdint.h>

#ifndef DEBUG_ALLOC

#define MALLOC(N) zmalloc(N)
#define CALLOC(N) zcalloc(N)
#define REALLOC(LOC, N) zrealloc(LOC, N)
#define FREE(PTR) zfree(PTR)

void* zmalloc(uint64_t length);
void* zcalloc(uint64_t length);
void* zrealloc(void* old, uint64_t length);
void zfree(void* ptr);

#else


#define MALLOC(N) zmalloc(N, __FILE__, __LINE__)
#define CALLOC(N) zcalloc(N, __FILE__, __LINE__)
#define REALLOC(LOC, N) zrealloc(LOC, N, __FILE__, __LINE__)
#define FREE(PTR) zfree(PTR, __FILE__, __LINE__)

void* zmalloc(uint64_t length, const char* file, int line);
void* zcalloc(uint64_t length, const char* file, int line);
void* zrealloc(void* old, uint64_t length, const char* file, int line);
void zfree(void* ptr, const char* file, int line);

extern int memory_total_allocated;

#endif