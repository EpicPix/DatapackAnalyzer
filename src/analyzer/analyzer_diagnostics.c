#include "analyzer_diagnostics.h"
#include "diagnostics.h"
#include "analyzer.h"
#include "../loader.h"
#include <stdlib.h>
#include <string.h>

void analyzer_add_diagnostic_range_msg_file_loc(struct analyzer_results *results, enum diagnostic_type type, const char* message, char* file, int line, int column, const char* min_version, const char* max_version) {
  int min = version_index(min_version);
  int max = version_index(max_version);
  struct diagnostics_info* diagnostic = NULL;
  for(int i = 0; i<results->version_count; i++) {
    struct datapack_results* datapack_result = &results->version_results[i];
    int index = datapack_result->version->index;

    if((index >= min || min == -1) && (index < max || max == -1)) {
      if(!diagnostic) {
        diagnostic = diagnostic_create_source_loc_dyn(type, message, file, line, column);
      }
      analyzer_add_diagnostic_specific(datapack_result, diagnostic);
    }
  }
  if(diagnostic) {
    if(diagnostic->source.filename) free(diagnostic->source.filename);
    free(diagnostic);
  }else {
    if(file) free(file);
  }
}

void analyzer_add_diagnostic_range_msg_file(struct analyzer_results *results, enum diagnostic_type type, const char* message, char* file, const char* min_version, const char* max_version) {
  analyzer_add_diagnostic_range_msg_file_loc(results, type, message, file, -1, -1, min_version, max_version);
}

void analyzer_add_diagnostic_range_msg(struct analyzer_results *results, enum diagnostic_type type, const char* message, const char* min_version, const char* max_version) {
  analyzer_add_diagnostic_range_msg_file_loc(results, type, message, NULL, -1, -1, min_version, max_version);
}

void analyzer_add_diagnostic_range(struct analyzer_results *results, const char* min_version, const char* max_version, struct diagnostics_info* diagnostic) {
  analyzer_add_diagnostic_range_index(results, version_index(min_version), version_index(max_version), diagnostic);
}

void analyzer_add_diagnostic_range_index(struct analyzer_results *results, int min_version, int max_version, struct diagnostics_info* diagnostic) {
  for(int i = 0; i<results->version_count; i++) {
    struct datapack_results* datapack_result = &results->version_results[i];
    int index = datapack_result->version->index;

    if((index >= min_version || min_version == -1) && (index < max_version || max_version == -1)) {
      analyzer_add_diagnostic_specific(datapack_result, diagnostic);
    }
  }
};

void analyzer_add_diagnostic_specific(struct datapack_results* result, struct diagnostics_info* diagnostic) {
  if(result->diagnostics_alloc <= result->diagnostics_count) {
    result->diagnostics_alloc *= 2;
    result->diagnostics = realloc(result->diagnostics, result->diagnostics_alloc * sizeof(struct diagnostics_info));
  }
  memcpy(&result->diagnostics[result->diagnostics_count], diagnostic, sizeof(struct diagnostics_info));
  struct diagnostics_info* diag = &result->diagnostics[result->diagnostics_count];
  diag->source.filename = clone_string(diag->source.filename);
  result->diagnostics_count++;
};