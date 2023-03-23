#pragma once

#include <stdbool.h>
#include <stdint.h>

struct version_info {
  const char *version_name;
  int datapack_format;
  uint16_t index;
  bool release;
};

extern const struct version_info VERSIONS[];
extern const int VERSION_COUNT;

uint16_t version_index(const char* name);
const struct version_info* version_from_index(uint16_t index);
const struct version_info* version_info(const char *name);
