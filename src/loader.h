#pragma once

#include <json-c/json.h>
#include <zip.h>
#include <stdint.h>

char *load_file(zip_t *zip, const char *file);
json_object *get_file_json(zip_t *zip, const char *filename);
int get_pack_format(zip_t *zip);

int64_t file_size(zip_t *zip, const char* name);
#define file_exists(zip, name) (file_size(zip, name) != -1)