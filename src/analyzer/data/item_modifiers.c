#include "data.h"
#include "../namespace.h"

void load_item_modifier(const char* namespace, struct zip_listing_index* entry, struct analysis_data *data, struct analyzer_results *results) {

};

void load_item_modifiers(const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace, "/item_modifiers/", load_item_modifier(namespace, entry, data, results));
};