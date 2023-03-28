#include "data.h"
#include "../namespace.h"
#include "commands/commands.h"

void load_function(struct zip_listing_index* namespace_index, struct zip_listing_index* entry, struct analysis_data *data, struct analyzer_results *results) {
  char* content = load_file_entry(entry);
  load_commands(namespace_index, entry, content, data, results);
  unload_file_entry(entry);
};

void load_functions(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace_index, "functions/", load_function(namespace_index, entry, data, results));
};