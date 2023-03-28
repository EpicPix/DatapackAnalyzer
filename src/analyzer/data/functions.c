#include "data.h"
#include "../namespace.h"
#include "commands/commands.h"

struct info_data {
  struct zip_listing_index* namespace_index;
  struct analysis_data *data;
  struct analyzer_results *results;
};

void load_function(struct zip_listing_index* entry, void* args) {
  struct info_data* d = args;
  load_commands(d->namespace_index, entry, load_file_entry(entry), d->data, d->results);
};

void load_functions(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results) {
  struct info_data d = { .namespace_index = namespace_index, .data = data, .results = results };
  list_namespace_files_foreach(namespace_index, "functions/", &load_function, &d);
};