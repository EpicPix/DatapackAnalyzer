#include "analyzer/analyzer.h"
#include "loader.h"
#include "versions.h"
#include <json-c/json.h>
#include <stdint.h>
#include <stdio.h>
#include <zip.h>
#include "write_file.h"

void write_result(struct datapack_results* results, FILE* file) {
    writestr(file, results->version->version_name);
    write32(file, results->diagnostics_count);
    for(int j = 0; j<results->diagnostics_count; j++) {
      struct diagnostics_info* diagnostic = &results->diagnostics[j];
      write8(file, diagnostic->type);
      writestr(file, diagnostic->message);
      free(diagnostic->message);
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

  zip_t *zip = zip_open(argv[1], ZIP_RDONLY, NULL);
  if (!zip)
    return 1;

  struct analyzer_results *results = analyze_datapack(zip);
  if(result_fd)
    write16(result_fd, results->version_count);

  for(int i = 0; i<results->version_count; i++) {
    struct datapack_results* datapack_result = &results->version_results[i];
    if(result_fd) {
      write_result(datapack_result, result_fd);
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
        free(diagnostic->message);
      }
    }
    free(datapack_result->diagnostics);
  }
  free(results->version_results);
  free(results);

  zip_close(zip);

  if(result_fd) {
    fclose(result_fd);
  }
  return 0;
}