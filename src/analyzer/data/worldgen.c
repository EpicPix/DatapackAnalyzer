#include "data.h"
#include "../namespace.h"

void load_worldgen(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};

void load_worldgens(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(zip, namespace, "/worldgen/", load_worldgen(zip, namespace, filename, data, results));
};