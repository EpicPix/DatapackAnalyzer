#pragma once

#include <endian.h>
#include <string.h>
#include <stdio.h>

struct file_result_data {
  FILE *file;
  long index;
  char data[8192];
};

#define write_flush(RESULT) { \
  fwrite(&RESULT->data, 1, RESULT->index, RESULT->file); \
  RESULT->index = 0; \
}

#define write_ensure_space(RESULT, MIN) { \
  if(RESULT->index + (MIN) >= 8192) { \
    write_flush(RESULT) \
  } \
}

#define write8(RESULT, VALUE) { \
  write_ensure_space(RESULT, 1); \
  RESULT->data[RESULT->index++] = VALUE; \
}

#define write16(RESULT, VALUE) { \
  write_ensure_space(RESULT, 2); \
  RESULT->data[RESULT->index++] = VALUE; \
  RESULT->data[RESULT->index++] = VALUE >> 8; \
}

#define write32(RESULT, VALUE) { \
  write_ensure_space(RESULT, 4); \
  RESULT->data[RESULT->index++] = VALUE; \
  RESULT->data[RESULT->index++] = VALUE >> 8; \
  RESULT->data[RESULT->index++] = VALUE >> 16; \
  RESULT->data[RESULT->index++] = VALUE >> 24; \
}

#define writestr(RESULT, VALUE) { \
  const char* val = VALUE; \
  if(val != NULL) { \
    int len = strlen(val); \
    write_ensure_space(RESULT, 2 + len); \
    RESULT->data[RESULT->index++] = len; \
    RESULT->data[RESULT->index++] = len >> 8; \
    memcpy(&RESULT->data[RESULT->index], val, len); \
    RESULT->index += len; \
  } else write16(RESULT, 0); \
}
