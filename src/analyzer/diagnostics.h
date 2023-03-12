#pragma once

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
  char* message;
  struct diagnostics_source_info source;
};

struct diagnostics_info* diagnostic_create(enum diagnostic_type type, const char* message);
struct diagnostics_info* diagnostic_create_source(enum diagnostic_type type, const char* message, const char* file);
struct diagnostics_info* diagnostic_create_source_dyn(enum diagnostic_type type, char* message, char* file);
struct diagnostics_info* diagnostic_create_source_loc(enum diagnostic_type type, const char* message, const char* file, int line, int column);
struct diagnostics_info* diagnostic_create_source_loc_dyn(enum diagnostic_type type, char* message, char* file, int line, int column);

#define diagnostic_clean(DIAGNOSTIC, OPERATION) \
{ \
  struct diagnostics_info* diagnostic = (DIAGNOSTIC); \
  OPERATION; \
  free(diagnostic->message); \
  if(diagnostic->source.filename) free(diagnostic->source.filename); \
  free(diagnostic); \
}
