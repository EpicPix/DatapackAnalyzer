#include "data.h"
#include "../namespace.h"

void load_advancement(struct zip_listing_index* namespace_index, struct zip_listing_index* index, struct analysis_data *data, struct analyzer_results *results) {

};

void load_advancements(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace_index, "advancements/", load_advancement(namespace_index, entry, data, results));
};