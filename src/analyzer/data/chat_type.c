#include "data.h"
#include "../namespace.h"

void load_chat_type(const char* namespace, struct zip_listing_index* index, struct analysis_data *data, struct analyzer_results *results) {

};

void load_chat_types(const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace, "/chat_type/", load_chat_type(namespace, entry, data, results));
};