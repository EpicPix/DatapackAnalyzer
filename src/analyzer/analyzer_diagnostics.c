#include "analyzer_diagnostics.h"
#include "diagnostics.h"
#include "analyzer.h"
#include "../loader.h"
#include <stdlib.h>
#include <string.h>

void analyzer_add_diagnostic_range_msg_file_loc(struct analyzer_results *results, enum diagnostic_type type, const char* message, char* file, int line, int column, const char* min_version, const char* max_version) {
  struct diagnostics_info* diagnostic = diagnostic_create_source_loc(type, message, file, line, column, min_version, max_version);
  analyzer_add_diagnostic_specific(results, diagnostic);
  if(file) free(file);
  if(diagnostic->source.filename) free(diagnostic->source.filename);
  free(diagnostic);
}

void analyzer_add_diagnostic_range_msg_file(struct analyzer_results *results, enum diagnostic_type type, const char* message, char* file, const char* min_version, const char* max_version) {
  analyzer_add_diagnostic_range_msg_file_loc(results, type, message, file, -1, -1, min_version, max_version);
}

void analyzer_add_diagnostic_range_msg(struct analyzer_results *results, enum diagnostic_type type, const char* message, const char* min_version, const char* max_version) {
  analyzer_add_diagnostic_range_msg_file_loc(results, type, message, NULL, -1, -1, min_version, max_version);
}

void analyzer_add_diagnostic_specific(struct analyzer_results* result, struct diagnostics_info* diagnostic) {
  if(result->diagnostics_alloc <= result->diagnostics_count) {
    result->diagnostics_alloc *= 2;
    result->diagnostics = realloc(result->diagnostics, result->diagnostics_alloc * sizeof(struct diagnostics_info));
  }
  memcpy(&result->diagnostics[result->diagnostics_count], diagnostic, sizeof(struct diagnostics_info));
  struct diagnostics_info* diag = &result->diagnostics[result->diagnostics_count];
  diag->source.filename = clone_string(diag->source.filename);
  result->diagnostics_count++;
};