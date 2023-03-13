#pragma once

#include <json-c/json.h>
#include <zip.h>
#include <stdint.h>

struct zip_listing_index {
  const char *filename;
  int size;
  unsigned int filename_size;
};

struct zip_listing_index_list {
  long count;
  struct zip_listing_index indexes[];
};

extern struct zip_listing_index_list* listing_index;

void load_listing(zip_t* zip);
void unload_listing();

char *load_file(zip_t *zip, const char *file);
json_object *get_file_json(zip_t *zip, const char *filename);
int get_pack_format(zip_t *zip);

int file_size(zip_t *zip, const char* name);
#define file_exists(zip, name) (file_size(zip, name) != -1)

char* clone_string(const char* data);