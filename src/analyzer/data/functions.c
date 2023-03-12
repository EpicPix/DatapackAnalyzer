#include "data.h"
#include "../namespace.h"
#include "commands/commands.h"

void load_function(zip_t* zip, const char* namespace, const char* filename, struct analysis_data *data, struct analyzer_results *results) {
  char* content = namespace_file_content(zip, namespace, filename+1);
  load_commands(zip, namespace, filename, content, data, results);
  free(content);
};

void load_functions(zip_t* zip, const char* namespace, struct analysis_data *data, struct analyzer_results *results) {
  list_namespace_files_foreach(zip, namespace, "/functions/", load_function(zip, namespace, filename, data, results));
};