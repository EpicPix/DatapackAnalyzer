#include "analyzer.h"
#include "../loader.h"
#include "../versions.h"
#include <stdlib.h>
#include <string.h>

struct analyzer_results *analyze_datapack(zip_t *zip) {
  struct analyzer_results *results = malloc(sizeof(struct analyzer_results));
  results->version_count = VERSION_COUNT;
  results->version_results = calloc(sizeof(struct datapack_results) * results->version_count, 1);
  for(int i = 0; i<results->version_count; i++) {
    results->version_results[i].version = &VERSIONS[i];
    results->version_results[i].diagnostics_alloc = 8;
    results->version_results[i].diagnostics = malloc(8 * sizeof(struct diagnostics_info));
  }

  int pack_format = get_pack_format(zip);
  analyzer_add_diagnostic_range_if(results, version->datapack_format != pack_format, diagnostic_create(diagnostic_warn, "Pack format does not match"));

  return results;
};

struct diagnostics_info* diagnostic_create(enum diagnostic_type type, const char* message) {
  return diagnostic_create_source(type, message, NULL);
}

struct diagnostics_info* diagnostic_create_source(enum diagnostic_type type, const char* message, const char* file) {
  return diagnostic_create_source_loc(type, message, file, -1, -1);
}

struct diagnostics_info* diagnostic_create_source_loc(enum diagnostic_type type, const char* message, const char* file, int line, int column) {
  struct diagnostics_info* info = malloc(sizeof(struct diagnostics_info));
  info->type = type;
  info->message = message;
  info->source.filename = file;
  info->source.line = line;
  info->source.column = column;
  return info;
}

void analyzer_add_diagnostic_range(struct analyzer_results *results, const char* min_version, const char* max_version, struct diagnostics_info* diagnostic) {
  analyzer_add_diagnostic_range_index(results, version_index(min_version), version_index(max_version), diagnostic);
}

void analyzer_add_diagnostic_range_index(struct analyzer_results *results, int min_version, int max_version, struct diagnostics_info* diagnostic) {
  for(int i = 0; i<results->version_count; i++) {
    struct datapack_results* datapack_result = &results->version_results[i];
    int index = datapack_result->version->index;

    if(index >= min_version && index <= max_version) {
      analyzer_add_diagnostic_specific(datapack_result, diagnostic);
    }
  }
};

void analyzer_add_diagnostic_specific(struct datapack_results* result, struct diagnostics_info* diagnostic) {
  if(result->diagnostics_alloc <= result->diagnostics_count) {
    result->diagnostics_alloc *= 2;
    result->diagnostics = realloc(result->diagnostics, result->diagnostics_alloc * sizeof(struct diagnostics_info));
  }
  memcpy(&result->diagnostics[result->diagnostics_count++], diagnostic, sizeof(struct diagnostics_info));
};