#include "data.h"
#include "../namespace.h"

void load_loot_table(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};

void load_loot_tables(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(zip, namespace, "/loot_tables/", load_loot_table(zip, namespace, filename, data, results));
};