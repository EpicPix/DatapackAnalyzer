#include "data.h"
#include "../namespace.h"

void load_item_modifier(struct zip_listing_index* namespace_index, struct zip_listing_index* entry, struct analysis_data *data, struct analyzer_results *results) {

};

void load_item_modifiers(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace_index, "item_modifiers/", load_item_modifier(namespace_index, entry, data, results));
};