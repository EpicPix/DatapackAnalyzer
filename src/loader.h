#pragma once

#include <json-c/json.h>
#include "zip/zip.h"
#include <stdint.h>

struct zip_listing_index {
  const char *filename;
  int size;
  int compressed_size;
  void* compressed_data;
  void* decompressed_data;
  unsigned int filename_size;
  int flags;
};

struct zip_listing_index_list {
  long count;
  struct zip_listing_index indexes[];
};

extern struct zip_listing_index_list* listing_index;

struct zip_listing_index* get_file_info(const char* filename);

char *load_file(const char *file);
char *load_file_entry(struct zip_listing_index* index);
void unload_file_entry(struct zip_listing_index* index);

json_object *get_file_json(const char *filename);
int get_pack_format();

int file_size(const char* name);
#define file_exists(name) (file_size(name) != -1)

char* clone_string(const char* data);
char* clone_string_len(const char* data, int len);