#include "data.h"
#include "../namespace.h"

void load_structure(const char* namespace, struct zip_listing_index* entry, struct analysis_data *data, struct analyzer_results *results) {

};

void load_structures(const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace, "/structures/", load_structure(namespace, entry, data, results));
};