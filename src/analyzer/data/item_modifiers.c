#include "data.h"
#include "../namespace.h"

void load_item_modifier(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};

void load_item_modifiers(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(zip, namespace, "/item_modifiers/", load_item_modifier(zip, namespace, filename, data, results));
};