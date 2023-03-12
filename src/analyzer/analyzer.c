#include "analyzer.h"
#include "diagnostics.h"
#include "analyzer_diagnostics.h"
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
