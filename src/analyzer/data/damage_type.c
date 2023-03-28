#include "data.h"
#include "../namespace.h"

void load_damage_type(struct zip_listing_index* namespace_index, struct zip_listing_index* index, struct analysis_data *data, struct analyzer_results *results) {

};

void load_damage_types(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace_index, "damage_type/", load_damage_type(namespace_index, entry, data, results));
};