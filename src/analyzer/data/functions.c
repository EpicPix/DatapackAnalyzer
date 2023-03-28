#include "data.h"
#include "../namespace.h"
#include "commands/commands.h"

void load_functions(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(namespace_index, "functions/", load_commands(namespace_index, entry, load_file_entry(entry), data, results));
};