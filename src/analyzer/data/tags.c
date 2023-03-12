#include "data.h"
#include "../../loader.h"
#include "../namespace.h"

void load_tags_blocks(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {

}

void load_tags_entity_types(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {

}

void load_tags_functions(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {

}

void load_tags_items(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {

}

void load_tags(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  if(namespace_file_exists(zip, namespace, "tags/entity_types/")) {
    diagnostic_create_source_dyn_range_clean(results, diagnostic_error, clone_string("Unable to use 'entity_types' tag data"), namespace_file_string(namespace, "tags/entity_types/"), version_index("17w49a"), version_index("18w43a"));
    load_tags_entity_types(zip, namespace, data, results);
  }

  if(namespace_file_exists(zip, namespace, "tags/functions/")) {
    diagnostic_create_source_dyn_range_clean(results, diagnostic_error, clone_string("Unable to use 'functions' tag data"), namespace_file_string(namespace, "tags/functions/"), version_index("17w49a"), version_index("17w49b"));
    load_tags_functions(zip, namespace, data, results);
  }

  if(namespace_file_exists(zip, namespace, "tags/blocks/")) {
    load_tags_blocks(zip, namespace, data, results);
  }

  if(namespace_file_exists(zip, namespace, "tags/items/")) {
    load_tags_items(zip, namespace, data, results);
  }
};