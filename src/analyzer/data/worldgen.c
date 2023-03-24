#include "data.h"
#include "../namespace.h"

void load_worldgen(const char* namespace, struct zip_listing_index* index, struct analysis_data *data, struct analyzer_results *results) {

};

void load_worldgens(const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace, "/worldgen/", load_worldgen(namespace, entry, data, results));
};