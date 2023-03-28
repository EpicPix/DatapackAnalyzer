#include "loader.h"
#include "memory.h"
#include <json-c/json.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <zlib.h>

struct zip_listing_index* get_file_info(const char* filename) {
  uint len = strlen(filename);
  for(int i = 0; i<listing_index->count; i++) {
    struct zip_listing_index* indx = &listing_index->indexes[i];
    if(indx->filename_size != len) continue;
    if(memcmp(indx->filename, filename, len) != 0) continue;
    return indx;
  }
  return NULL;
};

char *load_file(const char *filename) {
  struct zip_listing_index* index = get_file_info(filename);
  if(!index) return NULL;
  return load_file_entry(index);
}

static int file_data_length = -1;
static char* file_data = NULL;

void file_data_cleanup() {
  if(file_data) {
    FREE(file_data);
    file_data = NULL;
    file_data_length = -1;
  }
}

static inline void file_data_validate_length(int minimum) {
  if(file_data_length < minimum) {
    file_data_length = minimum;
    if(file_data) file_data = REALLOC(file_data, minimum);
    else file_data = MALLOC(minimum);
  }
}

// only one file at a time, don't try to parse 2 files at once
char *load_file_entry(struct zip_listing_index* index) {
  file_data_validate_length(index->size + 1);
  if((index->flags & 8) == 0) {
    memcpy(file_data, index->compressed_data, index->size);
    file_data[index->size] = '\0';
    return file_data;
  }

  z_stream stream = {
      .zalloc = Z_NULL,
      .zfree = Z_NULL,
      .opaque = Z_NULL,
      .avail_in = 0,
      .next_in = Z_NULL
  };
  int ret = inflateInit2(&stream, -MAX_WBITS);
  if(ret) {
    fprintf(stderr, "Inflate init failed: %s\n", zError(ret));
    exit(1);
  }
  stream.avail_in = index->compressed_size;
  stream.next_in = index->compressed_data;
  stream.avail_out = index->size;
  stream.next_out = (void*) file_data;
  ret = inflate(&stream, Z_FINISH);
  if(ret != Z_STREAM_END) {
    fprintf(stderr, "Inflate failed: %s\n", zError(ret));
    exit(1);
  }
  ret = inflateEnd(&stream);
  if(ret) {
    fprintf(stderr, "Inflate end failed: %s\n", zError(ret));
    exit(1);
  }
  file_data[index->size] = '\0';

  return file_data;
}

json_object *get_file_json(const char *filename) {
  char *file = load_file(filename);
  if (!file)
    return NULL;
  return json_tokener_parse(file);
}

int get_pack_format() {
  json_object *mcmeta_json = get_file_json("pack.mcmeta");
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

int file_size(const char* filename) {
  struct zip_listing_index* index = get_file_info(filename);
  if(!index) return -1;
  return index->size;
}


char* clone_string(const char* data) {
  if(data == NULL) return NULL;
  char* res = MALLOC(strlen(data) + 1);
  strcpy(res, data);
  return res;
}

char* clone_string_len(const char* data, int len) {
  if(data == NULL) return NULL;
  char* res = MALLOC(len + 1);
  memcpy(res, data, len);
  res[len] = '\0';
  return res;
}