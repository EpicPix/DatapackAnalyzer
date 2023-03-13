#include "commands.h"
#include "../../namespace.h"
#include <string.h>

void load_command(zip_t* zip, const char* namespace_name, const char* filename, int line_number, int column, const char* line, int line_length, struct analysis_data *data, struct analyzer_results *results) {
//    diagnostic_clean(
//      diagnostic_create_source_loc_dyn(diagnostic_error, "Invalid command", namespace_file_string(namespace_name, filename + 1), line_number, -1),
//      analyzer_add_diagnostic_all(results, diagnostic)
//    );
    int command_length = 0;
    while(command_length < line_length) {
      char c = line[command_length];
      if(c == ' ' || c == '\t') {
        break;
      }
      command_length++;
    }
    if(command_length == 4) {
      if(memcmp(line, "data", 4) == 0) {
        diagnostic_create_source_loc_dyn_range_clean(results, diagnostic_error, "Command `data` is not supported in this version", namespace_file_string(namespace_name, filename + 1), line_number, column, -1, version_index("17w45b"));
      }else if(memcmp(line, "ride", 4) == 0) {
        diagnostic_create_source_loc_dyn_range_clean(results, diagnostic_error, "Command `ride` is not supported in this version", namespace_file_string(namespace_name, filename + 1), line_number, column, -1, version_index("23w03a"));
      }
    }else if(command_length == 6) {
      if(memcmp(line, "damage", 6) == 0) {
        diagnostic_create_source_loc_dyn_range_clean(results, diagnostic_error, "Command `damage` is not supported in this version", namespace_file_string(namespace_name, filename + 1), line_number, column, -1, version_index("23w06a"));
      }
    }else if(command_length == 9) {
      if(memcmp(line, "attribute", 9) == 0) {
        diagnostic_create_source_loc_dyn_range_clean(results, diagnostic_error, "Command `attribute` is not supported in this version", namespace_file_string(namespace_name, filename + 1), line_number, column, -1, version_index("20w17a"));
      }else if(memcmp(line, "fillbiome", 9) == 0) {
        diagnostic_create_source_loc_dyn_range_clean(results, diagnostic_error, "Command `fillbiome` is not supported in this version", namespace_file_string(namespace_name, filename + 1), line_number, column, -1, version_index("22w46a"));
      }else if(memcmp(line, "blockdata", 10) == 0) {
        diagnostic_create_source_loc_dyn_range_clean(results, diagnostic_error, "Command `blockdata` is not supported in this version, use `data block`", namespace_file_string(namespace_name, filename + 1), line_number, column, version_index("17w45b"), -1);
      }
    }else if(command_length == 10) {
      if(memcmp(line, "entitydata", 10) == 0) {
        diagnostic_create_source_loc_dyn_range_clean(results, diagnostic_error, "Command `entitydata` is not supported in this version, use `data entity`", namespace_file_string(namespace_name, filename + 1), line_number, column, version_index("17w45b"), -1);
      }
    }else if(command_length == 11) {
      if(memcmp(line, "locatebiome", 11) == 0) {
        diagnostic_create_source_loc_dyn_range_clean(results, diagnostic_error, "Command `locatebiome` is not supported in this version", namespace_file_string(namespace_name, filename + 1), line_number, column, -1, version_index("20w06a"));
        diagnostic_create_source_loc_dyn_range_clean(results, diagnostic_error, "Command `locatebiome` is not supported in this version, use `locate biome`", namespace_file_string(namespace_name, filename + 1), line_number, column, version_index("22w19a"), -1);
      }else if(memcmp(line, "replaceitem", 11) == 0) {
        diagnostic_create_source_loc_dyn_range_clean(results, diagnostic_error, "Command `replaceitem` is not supported in this version, use `item replace`", namespace_file_string(namespace_name, filename + 1), line_number, column, version_index("20w46a"), -1);
      }
    }else if(command_length == 12) {
      if(memcmp(line, "placefeature", 12) == 0) {
        diagnostic_create_source_loc_dyn_range_clean(results, diagnostic_error, "Command `placefeature` is not supported in this version", namespace_file_string(namespace_name, filename + 1), line_number, column, -1, version_index("22w03a"));
        diagnostic_create_source_loc_dyn_range_clean(results, diagnostic_error, "Command `placefeature` is not supported in this version, use `place feature`", namespace_file_string(namespace_name, filename + 1), line_number, column, version_index("22w18a"), -1);
      }
    }
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
      load_command(zip, namespace_name, filename, line_number, 1, content + start, end - start, data, results);
      content[end] = endChar;
    }
  }
};