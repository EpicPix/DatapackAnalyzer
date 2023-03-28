#include "analyzer.h"
#include "diagnostics.h"
#include "analyzer_diagnostics.h"
#include "../memory.h"
#include "namespace.h"
#include "data/data.h"
#include "../loader.h"
#include "../versions.h"
#include <stdlib.h>
#include <string.h>

struct analyzer_results *analyze_datapack() {
  struct analyzer_results *results = MALLOC(sizeof(struct analyzer_results));
  results->diagnostics_count = 0;
  results->diagnostics_alloc = 8;
  results->diagnostics = MALLOC(8 * sizeof(struct diagnostics_info));

  struct analysis_data* analysis = MALLOC(sizeof(struct analysis_data));

  int pack_format = get_pack_format();
  const char* start_fail = NULL;
  const char* end_fail = NULL;
  for(int v = 0; v<VERSION_COUNT; v++) {
    if(VERSIONS[v].datapack_format != pack_format) {
      if(start_fail == NULL) start_fail = VERSIONS[v].version_name;
    }else {
      if(start_fail) {
        analyzer_add_diagnostic_range_msg_file(results, diagnostic_warn, "Pack format does not match", "pack.mcmeta", strlen("pack.mcmeta"), start_fail, NULL);
        start_fail = NULL;
      }
      end_fail = VERSIONS[v].version_name;
    }
  }
  if(end_fail) {
    analyzer_add_diagnostic_range_msg_file(results, diagnostic_warn, "Pack format does not match", "pack.mcmeta", strlen("pack.mcmeta"), NULL, end_fail);
  }

  struct zip_listing_index **result;
  int count = list_namespaces(&result);
  for(int i = 0; i<count; i++) {
    struct zip_listing_index* index = result[i];
    int filename_length = index->filename_size - 5 - 1;
    char* namespace = alloca(filename_length + 1);
    memcpy(namespace, index->filename + 5, filename_length);
    namespace[filename_length] = '\0';

    struct zip_listing_index* findex;

    if((findex = namespace_file_index(namespace, "damage_type/")) != NULL) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_error, "Unable to use 'damage_type' data", findex->filename, findex->filename_size, NULL, "23w06a");
      load_damage_types(index, analysis, results);
    }

    if((findex = namespace_file_index(namespace, "chat_type/")) != NULL) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_error, "Unable to use 'chat_type' data", findex->filename, findex->filename_size, NULL, "22w42a");
      load_chat_types(index, analysis, results);
    }

    if((findex = namespace_file_index(namespace, "item_modifiers/")) != NULL) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_error, "Unable to use 'item_modifiers' data", findex->filename, findex->filename_size, NULL, "20w46a");
      load_item_modifiers(index, analysis, results);
    }

    if((findex = namespace_file_index(namespace, "worldgen/")) != NULL) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_error, "Unable to use 'worldgen' data", findex->filename, findex->filename_size, NULL, "20w28a");
      load_worldgens(index, analysis, results);
    }

    if((findex = namespace_file_index(namespace, "predicates/")) != NULL) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_error, "Unable to use 'predicates' data", findex->filename, findex->filename_size, NULL, "19w38a");
      load_predicates(index, analysis, results);
    }

    if((findex = namespace_file_index(namespace, "tags/")) != NULL) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_error, "Unable to use 'tags' data", findex->filename, findex->filename_size, NULL, "17w49a");
      load_tags(index, analysis, results);
    }

    if((findex = namespace_file_index(namespace, "recipes/")) != NULL) {
      analyzer_add_diagnostic_range_msg_file(results, diagnostic_error, "Unable to use 'recipes' data", findex->filename, findex->filename_size, NULL, "17w48a");
      load_recipes(index, analysis, results);
    }

    if((findex = namespace_file_index(namespace, "advancements/")) != NULL) {
      load_advancements(index, analysis, results);
    }

    if((findex = namespace_file_index(namespace, "functions/")) != NULL) {
      load_functions(index, analysis, results);
    }

    if((findex = namespace_file_index(namespace, "loot_tables/")) != NULL) {
      load_loot_tables(index, analysis, results);
    }

    if((findex = namespace_file_index(namespace, "structures/")) != NULL) {
      load_structures(index, analysis, results);
    }
  }
  FREE(result);

  FREE(analysis);

  return results;
};
