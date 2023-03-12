#include "analyzer/analyzer.h"
#include "loader.h"
#include "versions.h"
#include <json-c/json.h>
#include <stdint.h>
#include <stdio.h>
#include <zip.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <datapack>\n", argv[0]);
    return 1;
  }
  zip_t *zip = zip_open(argv[1], ZIP_RDONLY, NULL);
  if (!zip)
    return 1;

  struct analyzer_results *results = analyze_datapack(zip);
  for(int i = 0; i<results->version_count; i++) {
    printf("Analyze version: %s\n", results->version_results[i].version);
    free(results->version_results[i].diagnostics);
  }
  free(results->version_results);
  free(results);

  zip_close(zip);
  return 0;
}