#include "analyzer.h"
#include "diagnostics.h"
#include "analyzer_diagnostics.h"
#include "namespace.h"
#include "data/data.h"
#include "../loader.h"
#include "../versions.h"
#include <stdlib.h>
#include <string.h>

struct analyzer_results *analyze_datapack() {
  struct analyzer_results *results = malloc(sizeof(struct analyzer_results));
  results->diagnostics_count = 0;
  results->diagnostics_alloc = 8;
  results->diagnostics = malloc(8 * sizeof(struct diagnostics_info));

  struct analysis_data* analysis = malloc(sizeof(struct analysis_data));

  int pack_format = get_pack_format();
  for(int v = 0; v<VERSION_COUNT; v++) {
    if(VERSIONS[v].datapack_format != pack_format) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_warn, "Pack format does not match", clone_string("pack.mcmeta"), VERSIONS[v].version_name, VERSIONS[v].version_name);
    }
  }

  char **result;
  int count = list_namespaces(&result);
  for(int i = 0; i<count; i++) {
    char* namespace = result[i];

    if(namespace_file_exists(namespace, "damage_type/")) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_error, "Unable to use 'damage_type' data", namespace_file_string(namespace, "damage_type/"), NULL, "23w06a");
      load_damage_types(namespace, analysis, results);
    }

    if(namespace_file_exists(namespace, "chat_type/")) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_error, "Unable to use 'chat_type' data", namespace_file_string(namespace, "chat_type/"), NULL, "22w42a");
      load_chat_types(namespace, analysis, results);
    }

    if(namespace_file_exists(namespace, "item_modifiers/")) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_error, "Unable to use 'item_modifiers' data", namespace_file_string(namespace, "item_modifiers/"), NULL, "20w46a");
      load_item_modifiers(namespace, analysis, results);
    }

    if(namespace_file_exists(namespace, "worldgen/")) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_error, "Unable to use 'worldgen' data", namespace_file_string(namespace, "worldgen/"), NULL, "20w28a");
      load_worldgens(namespace, analysis, results);
    }

    if(namespace_file_exists(namespace, "predicates/")) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_error, "Unable to use 'predicates' data", namespace_file_string(namespace, "predicates/"), NULL, "19w38a");
      load_predicates(namespace, analysis, results);
    }

    if(namespace_file_exists(namespace, "tags/")) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_error, "Unable to use 'tags' data", namespace_file_string(namespace, "tags/"), NULL, "17w49a");
      load_tags(namespace, analysis, results);
    }

    if(namespace_file_exists(namespace, "recipes/")) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_error, "Unable to use 'recipes' data", namespace_file_string(namespace, "recipes/"), NULL, "17w48a");
      load_recipes(namespace, analysis, results);
    }

    if(namespace_file_exists(namespace, "advancements/")) {
      load_advancements(namespace, analysis, results);
    }

    if(namespace_file_exists(namespace, "functions/")) {
      load_functions(namespace, analysis, results);
    }

    if(namespace_file_exists(namespace, "loot_tables/")) {
      load_loot_tables(namespace, analysis, results);
    }

    if(namespace_file_exists(namespace, "structures/")) {
      load_structures(namespace, analysis, results);
    }

    free(result[i]);
  }
  free(result);

  free(analysis);

  return results;
};
