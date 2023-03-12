#include "data.h"
#include "../namespace.h"

void load_function(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};

void load_functions(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(zip, namespace, "/functions/", load_function(zip, namespace, filename, data, results));
};