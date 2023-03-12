#include "analyzer.h"
#include "../loader.h"
#include "../versions.h"
#include <stdlib.h>

struct analyzer_results *analyze_datapack(zip_t *zip) {
  struct analyzer_results *results = malloc(sizeof(struct analyzer_results));
  results->version_count = VERSION_COUNT;
  results->version_results = calloc(sizeof(struct datapack_results) * results->version_count, 1);
  for(int i = 0; i<results->version_count; i++) {
    results->version_results[i].version = VERSIONS[i].version_name;
    results->version_results[i].diagnostics = malloc(sizeof(struct diagnostics_info*));
  }

  int pack_format = get_pack_format(zip);
  if (pack_format == -1) {
    printf("Invalid pack format: %d\n", pack_format);
  } else {
    printf("Pack format: %d\n", pack_format);
  }

  return results;
};