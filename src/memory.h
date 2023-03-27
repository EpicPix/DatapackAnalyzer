#pragma once

#include <stdint.h>

#define MALLOC(N) zmalloc(N)
#define CALLOC(N) zcalloc(N)
#define REALLOC(LOC, N) zrealloc(LOC, N)
#define FREE(PTR) zfree(PTR)

void* zmalloc(uint64_t length);
void* zcalloc(uint64_t length);
void* zrealloc(void* old, uint64_t length);
void zfree(void* ptr);