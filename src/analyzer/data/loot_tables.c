#include "data.h"
#include "../namespace.h"

void load_loot_table(const char* namespace, struct zip_listing_index* entry, struct analysis_data *data, struct analyzer_results *results) {

};

void load_loot_tables(const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace, "/loot_tables/", load_loot_table(namespace, entry, data, results));
};