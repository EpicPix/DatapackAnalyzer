#include "diagnostics.h"
#include "../loader.h"
#include "../versions.h"
#include "../memory.h"
#include <stdlib.h>

struct diagnostics_info* diagnostic_create_source(enum diagnostic_type type, const char* message, char* file, const char* min_version, const char* max_version) {
  return diagnostic_create_source_loc(type, message, file, -1, -1, min_version, max_version);
}

struct diagnostics_info* diagnostic_create_source_dyn(enum diagnostic_type type, const char* message, char* file, const char* min_version, const char* max_version) {
  return diagnostic_create_source_loc(type, message, file, -1, -1, min_version, max_version);
}

struct diagnostics_info* diagnostic_create_source_loc(enum diagnostic_type type, const char* message, char* file, int line, int column, const char* min_version, const char* max_version) {
  struct diagnostics_info* info = MALLOC(sizeof(struct diagnostics_info));
  info->type = type;
  info->min_version = version_index(min_version);
  info->max_version = version_index(max_version);
  info->message = message;
  info->source.filename = file;
  info->source.line = line;
  info->source.column = column;
  return info;
}
