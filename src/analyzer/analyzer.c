#include "analyzer.h"
#include "namespace.h"
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
  analyzer_add_diagnostic_range_if(results, version->datapack_format != pack_format, diagnostic_create_source(diagnostic_warn, "Pack format does not match", "pack.mcmeta"));

  if(!file_exists(zip, "data/")) {
    analyzer_add_diagnostic_all(results, diagnostic_create_source(diagnostic_info, "'data' folder does not exist", "data/"));
    return results;
  }

  char **result;
  int count = list_namespaces(zip, &result);
  for(int i = 0; i<count; i++) {
    char* namespace = result[i];

    if(namespace_file_exists(zip, namespace, "tags/")) {
      analyzer_add_diagnostic_range_index(results, -1, version_index("17w49a"), diagnostic_create(diagnostic_error, "Unable to use 'tags' data"));
    }

    if(namespace_file_exists(zip, namespace, "recipes/")) {
      analyzer_add_diagnostic_range_index(results, -1, version_index("17w48a"), diagnostic_create(diagnostic_error, "Unable to use 'recipes' data"));
    }

    if(namespace_file_exists(zip, namespace, "advancements/")) {

    }

    if(namespace_file_exists(zip, namespace, "functions/")) {

    }

    if(namespace_file_exists(zip, namespace, "loot_tables/")) {

    }

    if(namespace_file_exists(zip, namespace, "structures/")) {

    }

    //    printf("%s %ld %ld\n", result[i], strlen(result[i]), namespace_file_size(zip, result[i], "tags/"));
    //    char* content = namespace_file_content(zip, result[i], "tags/functions/load.json");

    free(result[i]);
  }
  free(result);

  return results;
};

char* clone_string(const char* data) {
  if(data == NULL) return NULL;
  char* res = malloc(strlen(data) + 1);
  strcpy(res, data);
  return res;
}

struct diagnostics_info* diagnostic_create(enum diagnostic_type type, const char* message) {
  return diagnostic_create_source(type, message, NULL);
}

struct diagnostics_info* diagnostic_create_source(enum diagnostic_type type, const char* message, const char* file) {
  return diagnostic_create_source_loc(type, message, file, -1, -1);
}

struct diagnostics_info* diagnostic_create_source_dyn(enum diagnostic_type type, char* message, char* file) {
  return diagnostic_create_source_loc_dyn(type, message, file, -1, -1);
}

struct diagnostics_info* diagnostic_create_source_loc(enum diagnostic_type type, const char* message, const char* file, int line, int column) {
  struct diagnostics_info* info = malloc(sizeof(struct diagnostics_info));
  info->type = type;
  info->message = clone_string(message);
  info->source.filename = clone_string(file);
  info->source.line = line;
  info->source.column = column;
  return info;
}

struct diagnostics_info* diagnostic_create_source_loc_dyn(enum diagnostic_type type, char* message, char* file, int line, int column) {
  struct diagnostics_info* info = malloc(sizeof(struct diagnostics_info));
  info->type = type;
  info->message = clone_string(message);
  free(message);
  info->source.filename = clone_string(file);
  free(file);
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
  diag->message = clone_string(diag->message);
  diag->source.filename = clone_string(diag->source.filename);
  result->diagnostics_count++;
};