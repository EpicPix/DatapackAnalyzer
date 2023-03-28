#include "data.h"
#include "../namespace.h"

void load_structure(struct zip_listing_index* namespace_index, struct zip_listing_index* entry, struct analysis_data *data, struct analyzer_results *results) {

};

void load_structures(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace_index, "structures/", load_structure(namespace_index, entry, data, results));
};