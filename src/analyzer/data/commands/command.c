#include "commands.h"
#include "../../namespace.h"
#include <string.h>

void load_command(zip_t* zip, const char* namespace_name, const char* filename, int line_number, const char* line, int line_length, struct analysis_data *data, struct analyzer_results *results) {
//    diagnostic_clean(
//      diagnostic_create_source_loc_dyn(diagnostic_error, "Invalid command", namespace_file_string(namespace_name, filename + 1), line_number, -1),
//      analyzer_add_diagnostic_all(results, diagnostic)
//    );
};

void load_commands(zip_t* zip, const char* namespace_name, const char* filename, char* content, struct analysis_data *data, struct analyzer_results *results) {
  int max_len = strlen(content);
  int line_number = 1;
  for(int i = 0; i<max_len; i++) {
    while(content[i] == '#') {
      while(i<max_len) {
        if(content[i] == '\n') {
          line_number++;
          break;
        }
        i++;
      }
      continue;
    }
    int start = i;
    while(i<max_len) {
      if(content[i] == '\n') {
        line_number++;
        break;
      }
      i++;
    }
    int end = i;
    if(end != start) {
      char endChar = content[end];
      content[end] = '\0';
      load_command(zip, namespace_name, filename, line_number, content + start, end - start, data, results);
      content[end] = endChar;
    }
  }
};