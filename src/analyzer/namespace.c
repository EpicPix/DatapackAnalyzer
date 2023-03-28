#include "namespace.h"
#include "../loader.h"
#include "../memory.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int list_namespaces(struct zip_listing_index ***result) {
  int result_count = 0;
  int alloc_count = 8;
  *result = MALLOC(alloc_count * sizeof(char**));

  int entry_count = listing_index->count;
  for(int i = 0; i<entry_count; i++) {
    struct zip_listing_index* entry = &listing_index->indexes[i];
    const char* ename = entry->filename;
    int name_length = entry->filename_size;
    if(name_length > 5 && ename[name_length - 1] == '/' && memcmp(ename, "data/", 5) == 0) {
      bool valid = true;
      for(int j = 5; j<name_length - 1; j++) {
        if(ename[j] == '/') {
          valid = false;
          break;
        }
      }
      if(valid) {
        if(result_count >= alloc_count) {
          alloc_count *= 2;
          *result = REALLOC(*result, alloc_count * sizeof(char**));
        }
        (*result)[result_count++] = entry;
      }
    }
  }

  return result_count;
}

int list_namespace_files(struct zip_listing_index* namespace_index, char* loc, struct zip_listing_index ***result) {
  int result_count = 0;
  int alloc_count = 8;
  *result = MALLOC(alloc_count * sizeof(char**));
  int loc_length = strlen(loc);
  int namespace_length = namespace_index->filename_size;
  int min_len = namespace_length + loc_length;

  int entry_count = listing_index->count;
  for(int i = 0; i<entry_count; i++) {
    struct zip_listing_index* entry = &listing_index->indexes[i];
    const char* ename = entry->filename;
    int name_length = entry->filename_size;
    if(name_length > min_len &&
        ename[name_length - 1] != '/' &&
        memcmp(ename, namespace_index->filename, namespace_length) == 0 &&
        memcmp(ename + namespace_length, loc, loc_length) == 0) {
      if(result_count >= alloc_count) {
        alloc_count *= 2;
        *result = REALLOC(*result, alloc_count * sizeof(char**));
      }
      (*result)[result_count++] = entry;
    }
  }

  return result_count;
}

void namespace_file_string_buf(const char *namespace_name, const char *file_name, char* buffer) {
  int namespace_len = strlen(namespace_name);
  int filename_len = strlen(file_name);

  memcpy(buffer, "data/", 5);
  memcpy(buffer + 5, namespace_name, namespace_len);
  buffer[5 + namespace_len] = '/';
  memcpy(buffer + 6 + namespace_len, file_name, filename_len);
  buffer[5 + namespace_len + 1 + filename_len] = '\0';
}

char* namespace_file_string(const char *namespace_name, const char *file_name) {
  int namespace_len = strlen(namespace_name);
  int filename_len = strlen(file_name);

  char* lookup = MALLOC(5 + namespace_len + 1 + filename_len + 1);
  memcpy(lookup, "data/", 5);
  memcpy(lookup + 5, namespace_name, namespace_len);
  lookup[5 + namespace_len] = '/';
  memcpy(lookup + 6 + namespace_len, file_name, filename_len);
  lookup[5 + namespace_len + 1 + filename_len] = '\0';

  return lookup;
}

struct zip_listing_index* namespace_file_index(const char *namespace_name, const char *file_name) {
  char* lookup = alloca(strlen(namespace_name) + strlen(file_name) + 7);
  namespace_file_string_buf(namespace_name, file_name, lookup);
  return get_file_info(lookup);
}

struct zip_listing_index* namespace_file_index_by_index(struct zip_listing_index* namespace, const char *file_name) {
  int filename_len = strlen(file_name);

  char* lookup = alloca(namespace->filename_size + filename_len + 1);
  memcpy(lookup, namespace->filename, namespace->filename_size);
  memcpy(lookup + namespace->filename_size, file_name, filename_len);
  lookup[namespace->filename_size + filename_len] = '\0';
  return get_file_info(lookup);
}