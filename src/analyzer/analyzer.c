#include "analyzer.h"
#include "diagnostics.h"
#include "analyzer_diagnostics.h"
#include "namespace.h"
#include "data/data.h"
#include "../loader.h"
#include "../versions.h"
#include <stdlib.h>
#include <string.h>

struct analyzer_results *analyze_datapack(zip_t *zip, const struct version_info* specific_version) {
  struct analyzer_results *results = malloc(sizeof(struct analyzer_results));
  if(!specific_version) {
    results->version_count = VERSION_COUNT;
    results->version_results = calloc(sizeof(struct datapack_results) * results->version_count, 1);
    for(int i = 0; i<results->version_count; i++){
      results->version_results[i].version = &VERSIONS[i];
      results->version_results[i].diagnostics_alloc = 8;
      results->version_results[i].diagnostics = malloc(8 * sizeof(struct diagnostics_info));
    }
  }else {
    results->version_count = 1;
    results->version_results = calloc(sizeof(struct datapack_results) * results->version_count, 1);
    results->version_results[0].version = specific_version;
    results->version_results[0].diagnostics_alloc = 8;
    results->version_results[0].diagnostics = malloc(8 * sizeof(struct diagnostics_info));
  }

  struct analysis_data* analysis = malloc(sizeof(struct analysis_data));

  int pack_format = get_pack_format(zip);
  diagnostic_create_source_if_clean(results, diagnostic_warn, "Pack format does not match", "pack.mcmeta", version->datapack_format != pack_format);

  char **result;
  int count = list_namespaces(zip, &result);
  for(int i = 0; i<count; i++) {
    char* namespace = result[i];

    if(namespace_file_exists(zip, namespace, "damage_type/")) {
      analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use 'damage_type' data", namespace_file_string(namespace, "damage_type/"), -1, -1, NULL, "23w06a");
      load_damage_types(zip, namespace, analysis, results);
    }

    if(namespace_file_exists(zip, namespace, "chat_type/")) {
      analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use 'chat_type' data", namespace_file_string(namespace, "chat_type/"), -1, -1, NULL, "22w42a");
      load_chat_types(zip, namespace, analysis, results);
    }

    if(namespace_file_exists(zip, namespace, "item_modifiers/")) {
      analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use 'item_modifiers' data", namespace_file_string(namespace, "item_modifiers/"), -1, -1, NULL, "20w46a");
      load_item_modifiers(zip, namespace, analysis, results);
    }

    if(namespace_file_exists(zip, namespace, "worldgen/")) {
      analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use 'worldgen' data", namespace_file_string(namespace, "worldgen/"), -1, -1, NULL, "20w28a");
      load_worldgens(zip, namespace, analysis, results);
    }

    if(namespace_file_exists(zip, namespace, "predicates/")) {
      analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use 'predicates' data", namespace_file_string(namespace, "predicates/"), -1, -1, NULL, "19w38a");
      load_predicates(zip, namespace, analysis, results);
    }

    if(namespace_file_exists(zip, namespace, "tags/")) {
      analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use 'tags' data", namespace_file_string(namespace, "tags/"), -1, -1, NULL, "17w49a");
      load_tags(zip, namespace, analysis, results);
    }

    if(namespace_file_exists(zip, namespace, "recipes/")) {
      analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use 'recipes' data", namespace_file_string(namespace, "recipes/"), -1, -1, NULL, "17w48a");
      load_recipes(zip, namespace, analysis, results);
    }

    if(namespace_file_exists(zip, namespace, "advancements/")) {
      load_advancements(zip, namespace, analysis, results);
    }

    if(namespace_file_exists(zip, namespace, "functions/")) {
      load_functions(zip, namespace, analysis, results);
    }

    if(namespace_file_exists(zip, namespace, "loot_tables/")) {
      load_loot_tables(zip, namespace, analysis, results);
    }

    if(namespace_file_exists(zip, namespace, "structures/")) {
      load_structures(zip, namespace, analysis, results);
    }

    free(result[i]);
  }
  free(result);

  free(analysis);

  return results;
};
