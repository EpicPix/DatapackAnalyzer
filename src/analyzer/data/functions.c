#include "data.h"
#include "../namespace.h"
#include "commands/commands.h"

void load_function(const char* namespace, struct zip_listing_index* entry, struct analysis_data *data, struct analyzer_results *results) {
  char* content = load_file_entry(entry);
  load_commands(namespace, entry, content, data, results);
  unload_file_entry(entry);
};

void load_functions(const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace, "/functions/", load_function(namespace, entry, data, results));
};