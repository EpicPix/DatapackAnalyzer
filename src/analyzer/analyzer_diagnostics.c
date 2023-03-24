#include "analyzer_diagnostics.h"
#include "diagnostics.h"
#include "analyzer.h"
#include "../loader.h"
#include <stdlib.h>
#include <string.h>

void analyzer_add_diagnostic_range_msg_file_loc(struct analyzer_results *result, enum diagnostic_type type, const char* message, char* file, int line, int column, const char* min_version, const char* max_version) {
  if(result->diagnostics_alloc <= result->diagnostics_count) {
    result->diagnostics_alloc *= 2;
    result->diagnostics = realloc(result->diagnostics, result->diagnostics_alloc * sizeof(struct diagnostics_info));
  }

  struct diagnostics_info* info = &result->diagnostics[result->diagnostics_count];
  info->type = type;
  info->min_version = version_index(min_version);
  info->max_version = version_index(max_version);
  info->message = message;
  info->source.filename = file;
  info->source.line = line;
  info->source.column = column;

  result->diagnostics_count++;
}

void analyzer_add_diagnostic_range_msg_file(struct analyzer_results *results, enum diagnostic_type type, const char* message, char* file, const char* min_version, const char* max_version) {
  analyzer_add_diagnostic_range_msg_file_loc(results, type, message, file, -1, -1, min_version, max_version);
}

void analyzer_add_diagnostic_range_msg(struct analyzer_results *results, enum diagnostic_type type, const char* message, const char* min_version, const char* max_version) {
  analyzer_add_diagnostic_range_msg_file_loc(results, type, message, NULL, -1, -1, min_version, max_version);
}