#include "data.h"
#include "../namespace.h"

void load_advancement(const char* namespace, struct zip_listing_index* index, struct analysis_data *data, struct analyzer_results *results) {

};

void load_advancements(const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace, "/advancements/", load_advancement(namespace, entry, data, results));
};