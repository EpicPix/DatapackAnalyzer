#include "data.h"
#include "../namespace.h"

void load_damage_type(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};

void load_damage_types(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(zip, namespace, "/damage_type/", load_damage_type(zip, namespace, filename, data, results));
};