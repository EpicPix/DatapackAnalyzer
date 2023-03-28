#include "data.h"
#include "../../loader.h"
#include "../namespace.h"
#include <string.h>

struct info_data {
  struct zip_listing_index* namespace_index;
  struct analysis_data *data;
  struct analyzer_results *results;
};

void load_tags_block(struct zip_listing_index* index, void* args) {

};

void load_tags_entity_type(struct zip_listing_index* index, void* args) {

};
void load_tags_function(struct zip_listing_index* index, void* args) {
  struct info_data* d = args;
  uint checkLength = strlen("data/minecraft/tags/functions/xxxx.json");
  if(index->filename_size == checkLength) {
    if(memcmp(index->filename, "data/minecraft/tags/functions/load.json", checkLength) == 0) {
      analyzer_add_diagnostic_range_msg_file_loc(d->results, diagnostic_error, "Unable to use the load tag in this version", index->filename, index->filename_size, -1, -1, "17w49a", "18w01a");
    }else if(memcmp(index->filename, "data/minecraft/tags/functions/tick.json", checkLength) == 0) {
      analyzer_add_diagnostic_range_msg_file_loc(d->results, diagnostic_error, "Unable to use the tick tag in this version", index->filename, index->filename_size, -1, -1, "17w49a", "17w49b");
    }
  }
};

void load_tags_item(struct zip_listing_index* index, void* args) {

};


void load_tags(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results) {
  struct info_data d = { .namespace_index = namespace_index, .data = data, .results = results };
  struct zip_listing_index* findex;

  if((findex = namespace_file_index_by_index(namespace_index, "tags/entity_types/")) != NULL) {
    analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use 'entity_types' tag data", findex->filename, findex->filename_size, -1, -1, "17w49a", "18w43a");
    list_namespace_files_foreach(namespace_index, "tags/entity_types/", load_tags_entity_type, &d);
  }

  if((findex = namespace_file_index_by_index(namespace_index, "tags/functions/")) != NULL) {
    analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use 'functions' tag data", findex->filename, findex->filename_size, -1, -1, "17w49a", "17w49b");
    list_namespace_files_foreach(namespace_index, "tags/functions/", load_tags_function, &d);
  }

  if((findex = namespace_file_index_by_index(namespace_index, "tags/entity_types/")) != NULL) {
    list_namespace_files_foreach(namespace_index, "tags/blocks/", load_tags_block, &d);
  }

  if((findex = namespace_file_index_by_index(namespace_index, "tags/entity_types/")) != NULL) {
    list_namespace_files_foreach(namespace_index, "tags/items/", load_tags_item, &d);
  }
};