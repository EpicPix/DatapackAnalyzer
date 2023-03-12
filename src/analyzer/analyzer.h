#pragma once

#include "../versions.h"
#include <zip.h>

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

struct datapack_results {
  const struct version_info *version;
  struct diagnostics_info *diagnostics;
  int diagnostics_count;
  int diagnostics_alloc;
};

struct analyzer_results {
  int version_count;
  struct datapack_results *version_results;
};

struct analyzer_results *analyze_datapack(zip_t *zip);

struct diagnostics_info* diagnostic_create(enum diagnostic_type type, const char* message);
struct diagnostics_info* diagnostic_create_source(enum diagnostic_type type, const char* message, const char* file);
struct diagnostics_info* diagnostic_create_source_dyn(enum diagnostic_type type, char* message, char* file);
struct diagnostics_info* diagnostic_create_source_loc(enum diagnostic_type type, const char* message, const char* file, int line, int column);
struct diagnostics_info* diagnostic_create_source_loc_dyn(enum diagnostic_type type, char* message, char* file, int line, int column);

#define analyzer_add_diagnostic_range_if(RESULTS, EXPR, DIAGNOSTIC) \
{ \
  struct diagnostics_info* diag = (DIAGNOSTIC); \
  for(int RANGE = 0; RANGE<RESULTS->version_count; RANGE++) { \
    const struct version_info* version = RESULTS->version_results[RANGE].version; \
    if(EXPR) { \
      analyzer_add_diagnostic_specific(&RESULTS->version_results[RANGE], diag); \
    } \
  } \
}

#define analyzer_add_diagnostic_all(RESULTS, DIAGNOSTIC) \
{ \
  struct diagnostics_info* diag = (DIAGNOSTIC); \
  for(int RANGE = 0; RANGE<RESULTS->version_count; RANGE++) { \
    analyzer_add_diagnostic_specific(&RESULTS->version_results[RANGE], diag); \
  } \
}

void analyzer_add_diagnostic_range(struct analyzer_results *results, const char* min_version, const char* max_version, struct diagnostics_info* diagnostic);
void analyzer_add_diagnostic_range_index(struct analyzer_results *results, int min_version, int max_version, struct diagnostics_info* diagnostic);
void analyzer_add_diagnostic_specific(struct datapack_results* result, struct diagnostics_info* diagnostic);
