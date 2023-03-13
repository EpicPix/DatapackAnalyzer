#include "analyzer/analyzer.h"
#include "analyzer/analyzer_diagnostics.h"
#include "loader.h"
#include "versions.h"
#include <json-c/json.h>
#include <stdint.h>
#include <stdio.h>
#include <zip.h>
#include "write_file.h"

void write_result(struct datapack_results* results, struct file_result_data *file) {
    writestr(file, results->version->version_name);
    write32(file, results->diagnostics_count);
    for(int j = 0; j<results->diagnostics_count; j++) {
      struct diagnostics_info* diagnostic = &results->diagnostics[j];
      write8(file, diagnostic->type);
      writestr(file, diagnostic->message);
      writestr(file, diagnostic->source.filename);
      if(diagnostic->source.filename) free(diagnostic->source.filename);
      write32(file, diagnostic->source.line);
      write32(file, diagnostic->source.column);
    }
};

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <datapack> [result_file]\n", argv[0]);
    return 1;
  }

  const char* result_file = argc > 2 ? argv[2] : NULL;
  FILE* result_fd = result_file != NULL ? fopen(result_file, "w") : NULL;
  struct file_result_data* result_data;
  if(result_fd) {
    result_data = calloc(sizeof(struct file_result_data), 1);
    result_data->file = result_fd;
  }

  zip_t *zip = zip_open(argv[1], ZIP_RDONLY, NULL);
  if (!zip)
    return 1;

  load_listing(zip);

  struct analyzer_results *results = analyze_datapack(zip);
  if(result_data)
    write16(result_data, results->version_count);

  for(int i = 0; i<results->version_count; i++) {
    struct datapack_results* datapack_result = &results->version_results[i];
    if(result_data) {
      write_result(datapack_result, result_data);
    }else {
      printf("Analyze version: %s (%d)\n", datapack_result->version->version_name, datapack_result->diagnostics_count);
      for(int j = 0; j<datapack_result->diagnostics_count; j++) {
        struct diagnostics_info* diagnostic = &datapack_result->diagnostics[j];
        if(diagnostic->source.filename != NULL) {
          if(diagnostic->source.line != -1) {
            if(diagnostic->source.column != -1) {
              printf("- %d: %s, %s:%d:%d\n", diagnostic->type, diagnostic->message, diagnostic->source.filename, diagnostic->source.line, diagnostic->source.column);
            }else {
              printf("- %d: %s, %s:%d\n", diagnostic->type, diagnostic->message, diagnostic->source.filename, diagnostic->source.line);
            }
          }else {
            printf("- %d: %s, %s\n", diagnostic->type, diagnostic->message, diagnostic->source.filename);
          }
          free(diagnostic->source.filename);
        }else {
          printf("- %d: %s\n", diagnostic->type, diagnostic->message);
        }
      }
    }
    free(datapack_result->diagnostics);
  }
  free(results->version_results);
  free(results);

  unload_listing();
  zip_close(zip);

  write_flush(result_data);
  free(result_data);
  if(result_fd) {
    fclose(result_fd);
  }
  return 0;
}