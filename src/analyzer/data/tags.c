#include "data.h"
#include "../../loader.h"
#include "../namespace.h"

void load_tags_block(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};

void load_tags_entity_type(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};

void load_tags_function(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};

void load_tags_item(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};


void load_tags(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  if(namespace_file_exists(zip, namespace, "tags/entity_types/")) {
    diagnostic_create_source_dyn_range_clean(results, diagnostic_error, clone_string("Unable to use 'entity_types' tag data"), namespace_file_string(namespace, "tags/entity_types/"), version_index("17w49a"), version_index("18w43a"));
    list_namespace_files_foreach(zip, namespace, "/tags/entity_types/", load_tags_entity_type(zip, namespace, filename, data, results));
  }

  if(namespace_file_exists(zip, namespace, "tags/functions/")) {
    diagnostic_create_source_dyn_range_clean(results, diagnostic_error, clone_string("Unable to use 'functions' tag data"), namespace_file_string(namespace, "tags/functions/"), version_index("17w49a"), version_index("17w49b"));
    list_namespace_files_foreach(zip, namespace, "/tags/functions/", load_tags_function(zip, namespace, filename, data, results));
  }

  if(namespace_file_exists(zip, namespace, "tags/blocks/")) {
    list_namespace_files_foreach(zip, namespace, "/tags/blocks/", load_tags_block(zip, namespace, filename, data, results));
  }

  if(namespace_file_exists(zip, namespace, "tags/items/")) {
    list_namespace_files_foreach(zip, namespace, "/tags/items/", load_tags_item(zip, namespace, filename, data, results));
  }
};