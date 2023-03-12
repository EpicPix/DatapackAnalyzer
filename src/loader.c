#include "loader.h"
#include <json-c/json.h>
#include <stdlib.h>
#include <zip.h>

char *load_file(zip_t *zip, const char *filename) {
  int64_t size = file_size(zip, filename);
  if(size == -1)
    return NULL;

  zip_file_t *file = zip_fopen(zip, filename, 0);
  char *content = malloc(size + 1);
  zip_fread(file, content, size);
  content[size] = '\0';
  zip_fclose(file);
  return content;
}

json_object *get_file_json(zip_t *zip, const char *filename) {
  char *file = load_file(zip, filename);
  if (!file)
    return NULL;
  json_object *json = json_tokener_parse(file);
  free(file);
  return json;
}

int get_pack_format(zip_t *zip) {
  json_object *mcmeta_json = get_file_json(zip, "pack.mcmeta");
  if (!mcmeta_json)
    return -1;
  json_object *pack_json = json_object_object_get(mcmeta_json, "pack");
  if (!pack_json)
    return -1;
  json_object *pack_format_json =
      json_object_object_get(pack_json, "pack_format");
  if (!pack_format_json)
    return -1;
  if (!json_object_is_type(pack_format_json, json_type_int))
    return -1;
  int format = json_object_get_int64(pack_format_json);
  json_object_put(mcmeta_json);
  return format;
}

#define ZIP_STAT_REQUIRED (ZIP_STAT_NAME | ZIP_STAT_SIZE)

int64_t file_size(zip_t *zip, const char* name) {
  zip_stat_t stat;
  if(zip_stat(zip, "data/", 0, &stat) != 0)
    return -1;

  if((stat.valid & ZIP_STAT_REQUIRED) == ZIP_STAT_REQUIRED)
    return stat.size;

  return -1;
}