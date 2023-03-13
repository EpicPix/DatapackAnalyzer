#include "data.h"
#include "../../loader.h"
#include "../namespace.h"
#include <string.h>

void load_tags_block(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};

void load_tags_entity_type(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};

void load_tags_function(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {
    if(strcmp(namespace, "minecraft") == 0) {
      if(strcmp(filename, "/tags/functions/load.json") == 0) {
        analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use the load tag in this version", namespace_file_string(namespace, "tags/functions/load.json"), -1, -1, "17w49a", "18w01a");
      }else if(strcmp(filename, "/tags/functions/tick.json") == 0) {
        analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use the tick tag in this version", namespace_file_string(namespace, "tags/functions/tick.json"), -1, -1, "17w49a", "17w49b");
      }
    }
};

void load_tags_item(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};


void load_tags(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  if(namespace_file_exists(zip, namespace, "tags/entity_types/")) {
    analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use 'entity_types' tag data", namespace_file_string(namespace, "tags/entity_types/"), -1, -1, "17w49a", "18w43a");
    list_namespace_files_foreach(zip, namespace, "/tags/entity_types/", load_tags_entity_type(zip, namespace, filename, data, results));
  }

  if(namespace_file_exists(zip, namespace, "tags/functions/")) {
    analyzer_add_diagnostic_range_msg_file_loc(results, diagnostic_error, "Unable to use 'functions' tag data", namespace_file_string(namespace, "tags/functions/"), -1, -1, "17w49a", "17w49b");
    list_namespace_files_foreach(zip, namespace, "/tags/functions/", load_tags_function(zip, namespace, filename, data, results));
  }

  if(namespace_file_exists(zip, namespace, "tags/blocks/")) {
    list_namespace_files_foreach(zip, namespace, "/tags/blocks/", load_tags_block(zip, namespace, filename, data, results));
  }

  if(namespace_file_exists(zip, namespace, "tags/items/")) {
    list_namespace_files_foreach(zip, namespace, "/tags/items/", load_tags_item(zip, namespace, filename, data, results));
  }
};