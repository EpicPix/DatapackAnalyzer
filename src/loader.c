#include "loader.h"
#include <json-c/json.h>
#include <stdlib.h>
#include <zip.h>

char *load_file(zip_t *zip, const char *filename) {
  zip_stat_t stat;
  int result = zip_stat(zip, filename, 0, &stat);
  if (result)
    return NULL;

  zip_file_t *file = zip_fopen(zip, filename, 0);
  char *content = malloc(stat.size + 1);
  zip_fread(file, content, stat.size);
  content[stat.size] = '\0';
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