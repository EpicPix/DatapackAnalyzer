#include "commands.h"
#include "../../namespace.h"
#include <string.h>

#define COMMAND_DIAGNOSTIC_RANGE(CONTEXT, TYPE, VALUE, MIN_VERSION, MAX_VERSION) \
  analyzer_add_diagnostic_range_msg_file_loc(CONTEXT->results, TYPE, VALUE, namespace_file_string(CONTEXT->namespace_name, context->filename + 1), context->line_number, context->column, MIN_VERSION, MAX_VERSION)

struct command_load_context {
  const char* namespace_name;
  const char* filename;
  int line_number;
  int column;
  const char* line;
  int line_length;
  struct analysis_data *data;
  struct analyzer_results *results;
};

void load_command(zip_t* zip, struct command_load_context* context) {
  struct analyzer_results *results = context->results;
  const char* line = context->line;

  int command_length = 0;
  while(command_length < context->line_length) {
    char c = line[command_length];
    if(c == ' ' || c == '\t') {
      break;
    }
    command_length++;
  }
  if(command_length == 4) {
    if(memcmp(line, "data", 4) == 0) {
      COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `data` is not supported in this version", NULL, "17w45b");
    }else if(memcmp(line, "ride", 4) == 0) {
      COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `ride` is not supported in this version", NULL, "23w03a");
    }
  }else if(command_length == 6) {
    if(memcmp(line, "damage", 6) == 0) {
      COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `damage` is not supported in this version", NULL, "23w06a");
    }
  }else if(command_length == 9) {
    if(memcmp(line, "attribute", 9) == 0) {
      COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `attribute` is not supported in this version", NULL, "20w17a");
    }else if(memcmp(line, "fillbiome", 9) == 0) {
      COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `fillbiome` is not supported in this version", NULL, "22w46a");
    }else if(memcmp(line, "blockdata", 10) == 0) {
      COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `blockdata` is not supported in this version, use `data block`", "17w45b", NULL);
    }
  }else if(command_length == 10) {
    if(memcmp(line, "entitydata", 10) == 0) {
      COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `entitydata` is not supported in this version, use `data entity`", "17w45b", NULL);
    }
  }else if(command_length == 11) {
    if(memcmp(line, "locatebiome", 11) == 0) {
      COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `locatebiome` is not supported in this version", NULL, "20w06a");
      COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `locatebiome` is not supported in this version, use `locate biome`", "22w19a", NULL);
    }else if(memcmp(line, "replaceitem", 11) == 0) {
      COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `replaceitem` is not supported in this version, use `item replace`", "20w46a", NULL);
    }
  }else if(command_length == 12) {
    if(memcmp(line, "placefeature", 12) == 0) {
      COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `placefeature` is not supported in this version", NULL, "22w03a");
      COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `placefeature` is not supported in this version, use `place feature`", "22w18a", NULL);
    }
  }
};

void load_commands(zip_t* zip, const char* namespace_name, const char* filename, char* content, struct analysis_data *data, struct analyzer_results *results) {
  int max_len = strlen(content);
  int line_number = 1;
  for(int i = 0; i<max_len; i++) {
  do_loop:
    if(content[i] == '#') {
      while(i<max_len) {
        if(content[i++] == '\n') {
          line_number++;
          break;
        }
      }
      goto do_loop;
    }
    int start = i;
    while(i<max_len) {
      if(content[i++] == '\n') {
        line_number++;
        goto do_loop;
      }
    }
    int end = i;
    if(end != start) {
      char endChar = content[end];
      content[end] = '\0';
      struct command_load_context context = {
          .namespace_name = namespace_name,
          .filename = filename,
          .line_number = line_number,
          .column = 1,
          .line = content + start,
          .line_length = end - start,
          .data = data,
          .results = results,
      };
      load_command(zip, &context);
      content[end] = endChar;
    }
  }
};