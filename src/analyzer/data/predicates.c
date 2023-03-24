#include "data.h"
#include "../namespace.h"

void load_predicate(const char* namespace, struct zip_listing_index* entry, struct analysis_data *data, struct analyzer_results *results) {

};

void load_predicates(const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace, "/predicates/", load_predicate(namespace, entry, data, results));
};