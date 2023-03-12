#pragma once

#include <endian.h>
#include <string.h>

#define write8(FILE, VALUE) { \
  uint8_t value_input = VALUE; \
  fwrite(&value_input, 1, 1, FILE); \
}

#define write16(FILE, VALUE) { \
uint16_t value_input = htole16(VALUE); \
fwrite(&value_input, 1, 2, FILE); \
}

#define write32(FILE, VALUE) { \
uint32_t value_input = htole32(VALUE); \
fwrite(&value_input, 1, 4, FILE); \
}

#define write64(FILE, VALUE) { \
uint64_t value_input = htole64(VALUE); \
fwrite(&value_input, 1, 8, FILE); \
}

#define writestr(FILE, VALUE) { \
  const char* val = VALUE; \
  if(val != NULL) { \
    write16(FILE, strlen(val)); \
    fwrite(val, 1, strlen(val), FILE); \
  } else write16(FILE, 0); \
}
