#pragma once

#include "diagnostics.h"
#include "analyzer.h"

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

enum diagnostic_type;

void analyzer_add_diagnostic_range_msg_file_loc(struct analyzer_results *results, enum diagnostic_type type, const char* message, char* file, int line, int column, const char* min_version, const char* max_version);
void analyzer_add_diagnostic_range_msg_file(struct analyzer_results *results, enum diagnostic_type type, const char* message, char* file, const char* min_version, const char* max_version);
void analyzer_add_diagnostic_range_msg(struct analyzer_results *results, enum diagnostic_type type, const char* message, const char* min_version, const char* max_version);

void analyzer_add_diagnostic_range(struct analyzer_results *results, const char* min_version, const char* max_version, struct diagnostics_info* diagnostic);
void analyzer_add_diagnostic_range_index(struct analyzer_results *results, int min_version, int max_version, struct diagnostics_info* diagnostic);
void analyzer_add_diagnostic_specific(struct datapack_results* result, struct diagnostics_info* diagnostic);
