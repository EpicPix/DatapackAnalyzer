#include "data.h"
#include "../namespace.h"

void load_damage_type(const char* namespace, struct zip_listing_index* index, struct analysis_data *data, struct analyzer_results *results) {

};

void load_damage_types(const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace, "/damage_type/", load_damage_type(namespace, entry, data, results));
};