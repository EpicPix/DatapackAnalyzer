#include "data.h"
#include "../namespace.h"

void load_predicate(struct zip_listing_index* namespace_index, struct zip_listing_index* entry, struct analysis_data *data, struct analyzer_results *results) {

};

void load_predicates(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace_index, "predicates/", load_predicate(namespace_index, entry, data, results));
};