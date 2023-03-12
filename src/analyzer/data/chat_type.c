#include "data.h"
#include "../namespace.h"

void load_chat_type(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {

};

void load_chat_types(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(zip, namespace, "/chat_type/", load_chat_type(zip, namespace, filename, data, results));
};