#include "loader.h"
#include <json-c/json.h>
#include <stdlib.h>
#include <zip.h>
#include <string.h>

struct zip_listing_index_list* listing_index = NULL;

void load_listing(zip_t* zip) {
  unload_listing();


  int result_count = 0;
  int alloc_count = 8;
  listing_index = malloc(sizeof(struct zip_listing_index_list) + alloc_count * sizeof(struct zip_listing_index));

  int entry_count = zip_get_num_entries(zip, 0);
  for(int i = 0; i<entry_count; i++) {
    zip_stat_t stat;
    zip_stat_index(zip, i, 0, &stat);
    if(result_count >= alloc_count) {
      alloc_count *= 2;
      listing_index = realloc(listing_index, sizeof(struct zip_listing_index_list) + alloc_count * sizeof(struct zip_listing_index));
    }
    struct zip_listing_index* entry = &listing_index->indexes[result_count++];
    entry->size = stat.size;
    entry->filename = stat.name;
    int filename_length = strlen(stat.name);
    entry->filename_size = filename_length;
  }
  listing_index->count = result_count;
}

void unload_listing() {
  if(listing_index) {
    free(listing_index);
  }
}

char *load_file(zip_t *zip, const char *filename) {
  int64_t size = file_size(zip, filename);
  if(size != -1) {
    zip_file_t *file = zip_fopen(zip, filename, 0);
    char *content = malloc(size + 1);
    zip_fread(file, content, size);
    content[size] = '\0';
    zip_fclose(file);
    return content;
  }
  return NULL;
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

int file_size(zip_t *zip, const char* name) {
  zip_stat_t stat;
  if(zip_stat(zip, name, 0, &stat) == 0)
    return stat.size;

  return -1;
}


char* clone_string(const char* data) {
  if(data == NULL) return NULL;
  char* res = malloc(strlen(data) + 1);
  strcpy(res, data);
  return res;
}