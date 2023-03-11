#include "loader.h"
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

  char *mcmeta = load_file(zip, "pack.mcmeta");
  struct json_object *mcmeta_json = json_tokener_parse(mcmeta);
  free(mcmeta);

  struct json_object *pack_json = json_object_object_get(mcmeta_json, "pack");
  struct json_object *pack_format_json =
      json_object_object_get(pack_json, "pack_format");
  printf("pack format: %ld\n", json_object_get_int64(pack_format_json));
  json_object_put(mcmeta_json);

  zip_close(zip);
  return 0;
}