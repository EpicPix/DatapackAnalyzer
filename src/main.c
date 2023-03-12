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

  for (int i = 0; i < VERSION_COUNT; i++) {
    printf("%s\n", VERSIONS[i].version_name);
  }

  int pack_format = get_pack_format(zip);
  if (pack_format == -1) {
    printf("Invalid pack format: %d\n", pack_format);
  } else {
    printf("Pack format: %d\n", pack_format);
  }

  zip_close(zip);
  return 0;
}