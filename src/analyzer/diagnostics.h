#pragma once
#include <stdint.h>
#include "analyzer_diagnostics.h"

enum diagnostic_type {
  diagnostic_info = 0,
  diagnostic_warn = 1,
  diagnostic_error = 2,
};

struct diagnostics_source_info {
  char* filename;
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

struct diagnostics_info* diagnostic_create_source(enum diagnostic_type type, const char* message, const char* file, const char* min_version, const char* max_version);
struct diagnostics_info* diagnostic_create_source_dyn(enum diagnostic_type type, const char* message, char* file, const char* min_version, const char* max_version);
struct diagnostics_info* diagnostic_create_source_loc(enum diagnostic_type type, const char* message, const char* file, int line, int column, const char* min_version, const char* max_version);
