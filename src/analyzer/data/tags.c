#include "data.h"
#include "../../loader.h"
#include "../namespace.h"
#include <string.h>

void load_tags_block(const char* namespace, struct zip_listing_index* index, struct analysis_data *data, struct analyzer_results *results) {

};

void load_tags_entity_type(const char* namespace, struct zip_listing_index* index, struct analysis_data *data, struct analyzer_results *results) {

};

void load_tags_function(const char* namespace, struct zip_listing_index* index, struct analysis_data *data, struct analyzer_results *results) {
  uint checkLength = strlen("data/minecraft/tags/functions/xxxx.json");
  if(index->filename_size == checkLength) {
    if(memcmp(index->filename, "data/minecraft/tags/functions/load.json", checkLength) == 0) {
      analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use the load tag in this version", clone_string_len(index->filename, index->filename_size), -1, -1, "17w49a", "18w01a");
    }else if(memcmp(index->filename, "data/minecraft/tags/functions/tick.json", checkLength) == 0) {
      analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use the tick tag in this version", clone_string_len(index->filename, index->filename_size), -1, -1, "17w49a", "17w49b");
    }
  }
};

void load_tags_item(const char* namespace, struct zip_listing_index* index, struct analysis_data *data, struct analyzer_results *results) {

};


void load_tags(const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  if(namespace_file_exists(namespace, "tags/entity_types/")) {
    analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use 'entity_types' tag data", namespace_file_string(namespace, "tags/entity_types/"), -1, -1, "17w49a", "18w43a");
    list_namespace_files_foreach(namespace, "/tags/entity_types/", load_tags_entity_type(namespace, entry, data, results));
  }

  if(namespace_file_exists(namespace, "tags/functions/")) {
    analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use 'functions' tag data", namespace_file_string(namespace, "tags/functions/"), -1, -1, "17w49a", "17w49b");
    list_namespace_files_foreach(namespace, "/tags/functions/", load_tags_function(namespace, entry, data, results));
  }

  if(namespace_file_exists(namespace, "tags/blocks/")) {
    list_namespace_files_foreach(namespace, "/tags/blocks/", load_tags_block(namespace, entry, data, results));
  }

  if(namespace_file_exists(namespace, "tags/items/")) {
    list_namespace_files_foreach(namespace, "/tags/items/", load_tags_item(namespace, entry, data, results));
  }
};