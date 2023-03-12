#include "analyzer.h"
#include "../loader.h"
#include "../versions.h"
#include <stdlib.h>
#include <string.h>

int list_namespaces(zip_t *zip, char ***result) {
  int result_count = 0;
  int alloc_count = 8;
  *result = malloc(alloc_count * sizeof(char**));

  int entry_count = zip_get_num_entries(zip, 0);
  for(int i = 0; i<entry_count; i++) {
    zip_stat_t stat;
    zip_stat_index(zip, i, 0, &stat);
    int name_length = strlen(stat.name);
    if(name_length > 5 && stat.name[name_length - 1] == '/' && strncmp(stat.name, "data/", 5) == 0) {
      bool valid = true;
      for(int j = 5; j<name_length - 1; j++) {
        if(stat.name[j] == '/') {
          valid = false;
          break;
        }
      }
      if(valid) {
        if(result_count >= alloc_count) {
          alloc_count *= 2;
          *result = realloc(*result, alloc_count * sizeof(char**));
        }
        char* namespace_name = malloc(name_length - 5);
        memcpy(namespace_name, stat.name + 5, name_length - 6);
        namespace_name[name_length - 6] = '\0';
        (*result)[result_count++] = namespace_name;
      }
    }
  }

  return result_count;
}

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
    printf("%s %ld\n", result[i], strlen(result[i]));

    free(result[i]);
  }
  free(result);

  return results;
};

struct diagnostics_info* diagnostic_create(enum diagnostic_type type, const char* message) {
  return diagnostic_create_source(type, message, "");
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