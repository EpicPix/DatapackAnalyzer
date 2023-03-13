#pragma once
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
  const char* message;
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
  if(diagnostic->source.filename) free(diagnostic->source.filename); \
  free(diagnostic); \
}

#define diagnostic_create_source_range_clean(results, type, message, file, min_version, max_version) \
{ \
  diagnostic_clean( \
      diagnostic_create_source(type, message, file), \
      analyzer_add_diagnostic_range_index(results, min_version, max_version, diagnostic) \
  ); \
}

#define diagnostic_create_source_dyn_range_clean(results, type, message, file, min_version, max_version) \
{ \
  diagnostic_clean( \
      diagnostic_create_source_dyn(type, message, file), \
      analyzer_add_diagnostic_range_index(results, min_version, max_version, diagnostic) \
  ); \
}

#define diagnostic_create_source_loc_dyn_range_clean(results, type, message, file, line, column, min_version, max_version) \
{ \
  diagnostic_clean( \
      diagnostic_create_source_loc_dyn(type, message, file, line, column), \
      analyzer_add_diagnostic_range_index(results, min_version, max_version, diagnostic) \
  ); \
}

#define diagnostic_create_source_if_clean(results, type, message, file, expression) \
{ \
  diagnostic_clean( \
      diagnostic_create_source(type, message, file), \
      analyzer_add_diagnostic_range_if(results, expression, diagnostic) \
  ); \
}

#define diagnostic_create_source_dyn_if_clean(results, type, message, file, expression) \
{ \
  diagnostic_clean( \
      diagnostic_create_source_dyn(type, message, file), \
      analyzer_add_diagnostic_range_if(results, expression, diagnostic) \
  ); \
}
