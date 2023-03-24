#include "data.h"
#include "../namespace.h"

void load_recipe(const char* namespace, struct zip_listing_index* entry, struct analysis_data *data, struct analyzer_results *results) {

};

void load_recipes(const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace, "/recipes/", load_recipe(namespace, entry, data, results));
};