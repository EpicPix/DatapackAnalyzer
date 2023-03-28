#include "data.h"
#include "../namespace.h"

void load_chat_type(struct zip_listing_index* namespace_index, struct zip_listing_index* index, struct analysis_data *data, struct analyzer_results *results) {

};

void load_chat_types(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace_index, "chat_type/", load_chat_type(namespace_index, entry, data, results));
};