#include "analyzer_diagnostics.h"
#include "diagnostics.h"
#include "analyzer.h"
#include "../loader.h"
#include <stdlib.h>
#include <string.h>

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
  diag->message = diag->message;
  diag->source.filename = clone_string(diag->source.filename);
  result->diagnostics_count++;
};