#pragma once
#include <stdint.h>
#include "analyzer_diagnostics.h"
#include "../memory.h"

enum diagnostic_type {
  diagnostic_info = 0,
  diagnostic_warn = 1,
  diagnostic_error = 2,
};

struct diagnostics_source_info {
  const char* filename;
  int filename_length;
  int line;
  int column;
};

struct diagnostics_info {
  enum diagnostic_type type;
  uint16_t min_version;
  uint16_t max_version;
  const char* message;
  struct diagnostics_source_info source;
};
