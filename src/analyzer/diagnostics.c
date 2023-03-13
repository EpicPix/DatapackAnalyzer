#include "diagnostics.h"
#include "../loader.h"
#include <stdlib.h>

struct diagnostics_info* diagnostic_create(enum diagnostic_type type, const char* message) {
  return diagnostic_create_source(type, message, NULL);
}

struct diagnostics_info* diagnostic_create_source(enum diagnostic_type type, const char* message, const char* file) {
  return diagnostic_create_source_loc(type, message, file, -1, -1);
}

struct diagnostics_info* diagnostic_create_source_dyn(enum diagnostic_type type, const char* message, char* file) {
  return diagnostic_create_source_loc_dyn(type, message, file, -1, -1);
}

struct diagnostics_info* diagnostic_create_source_loc(enum diagnostic_type type, const char* message, const char* file, int line, int column) {
  struct diagnostics_info* info = malloc(sizeof(struct diagnostics_info));
  info->type = type;
  info->message = message;
  info->source.filename = clone_string(file);
  info->source.line = line;
  info->source.column = column;
  return info;
}

struct diagnostics_info* diagnostic_create_source_loc_dyn(enum diagnostic_type type, const char* message, char* file, int line, int column) {
  struct diagnostics_info* info = malloc(sizeof(struct diagnostics_info));
  info->type = type;
  info->message = message;
  info->source.filename = clone_string(file);
  free(file);
  info->source.line = line;
  info->source.column = column;
  return info;
}
