#pragma once

#include <stdbool.h>

struct version_info {
  const char *version_name;
  int datapack_format;
  int index;
  bool release;
};

extern const struct version_info VERSIONS[];
extern const int VERSION_COUNT;

int version_index(const char* name);