#include "data.h"
#include "../namespace.h"

void load_advancement(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};

void load_advancements(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(zip, namespace, "/advancements/", load_advancement(zip, namespace, filename, data, results));
};