#include "analyzer/analyzer.h"
#include "analyzer/analyzer_diagnostics.h"
#include "diagnostics.h"
#include "loader.h"
#include "versions.h"
#include <json-c/json.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "write_file.h"
#include "zip/zip.h"

void write_results(struct analyzer_results* results, struct file_result_data *file) {
  write32(file, VERSION_COUNT);
  for(int i = 0; i<VERSION_COUNT; i++) {
    writestr(file, VERSIONS[i].version_name);
    write16(file, VERSIONS[i].index);
  }

  write32(file, results->diagnostics_count);
  for(int i = 0; i<results->diagnostics_count; i++) {
    struct diagnostics_info* diagnostic = &results->diagnostics[i];
    write8(file, diagnostic->type);
    write16(file, diagnostic->min_version);
    write16(file, diagnostic->max_version);
    writestr(file, diagnostic->message);
    writestr(file, diagnostic->source.filename);
    if(diagnostic->source.filename) free(diagnostic->source.filename);
    write32(file, diagnostic->source.line);
    write32(file, diagnostic->source.column);
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <datapack> [result_file] [version]\n", argv[0]);
    return 1;
  }

  const char* result_file = argc > 2 ? argv[2] : NULL;
  FILE* result_fd = (result_file != NULL && strcmp(result_file, "-") != 0) ? fopen(result_file, "w") : NULL;
  struct file_result_data* result_data = NULL;
  if(result_fd) {
    result_data = calloc(sizeof(struct file_result_data), 1);
    result_data->file = result_fd;
  }

  zip_open(argv[1]);

  struct analyzer_results *results = analyze_datapack();

  if(result_data) {
    write_results(results, result_data);
  }else {
    for(int i = 0; i<results->diagnostics_count; i++) {
      struct diagnostics_info* diagnostic = &results->diagnostics[i];

      const struct version_info* min = version_from_index(diagnostic->min_version);
      const struct version_info* max = version_from_index(diagnostic->max_version);

      if(diagnostic->source.filename != NULL) {
        printf("- %d %s..%s: %s, %s:%d:%d\n", diagnostic->type, min ? min->version_name : "", max ? max->version_name : "", diagnostic->message, diagnostic->source.filename, diagnostic->source.line, diagnostic->source.column);
        free(diagnostic->source.filename);
      }else {
        printf("- %d %s..%s: %s\n", diagnostic->type, min ? min->version_name : "", max ? max->version_name : "", diagnostic->message);
      }
    }
  }
  free(results->diagnostics);
  free(results);

  if(result_data) {
    write_flush(result_data);
    free(result_data);
  }
  zip_close();
  if(result_fd) {
    fclose(result_fd);
  }
  return 0;
}