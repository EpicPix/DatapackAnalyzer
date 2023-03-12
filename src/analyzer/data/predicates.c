#include "data.h"
#include "../namespace.h"

void load_predicate(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};

void load_predicates(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(zip, namespace, "/predicates/", load_predicate(zip, namespace, filename, data, results));
};