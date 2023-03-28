#include "data.h"
#include "../namespace.h"

struct info_data {
  struct zip_listing_index* namespace_index;
  struct analysis_data *data;
  struct analyzer_results *results;
};

void load_structure(struct zip_listing_index* index, void* args) {

};

void load_structures(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results) {
  struct info_data d = { .namespace_index = namespace_index, .data = data, .results = results };
  list_namespace_files_foreach(namespace_index, "structures/", load_structure, &d);
};