#include "data.h"
#include "../namespace.h"

struct info_data {
  struct zip_listing_index* namespace_index;
  struct analysis_data *data;
  struct analyzer_results *results;
};

void load_advancement(struct zip_listing_index* index, void* args) {

};

void load_advancements(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results) {
  struct info_data d = { .namespace_index = namespace_index, .data = data, .results = results };
  list_namespace_files_foreach(namespace_index, "advancements/", load_advancement, &d);
};