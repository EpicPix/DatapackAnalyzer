#include "namespace.h"
#include "../loader.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int list_namespaces(zip_t *zip, char ***result) {
  int result_count = 0;
  int alloc_count = 8;
  *result = malloc(alloc_count * sizeof(char**));

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
          *result = realloc(*result, alloc_count * sizeof(char**));
        }
        char* namespace_name = malloc(name_length - 5);
        memcpy(namespace_name, ename + 5, name_length - 6);
        namespace_name[name_length - 6] = '\0';
        (*result)[result_count++] = namespace_name;
      }
    }
  }

  return result_count;
}

int list_namespace_files(zip_t *zip, const char* namespace, char* loc, char ***result) {
  int result_count = 0;
  int alloc_count = 8;
  *result = malloc(alloc_count * sizeof(char**));
  int namespace_length = strlen(namespace);
  int loc_length = strlen(loc);
  int min_len = 5 + namespace_length + loc_length;

  int entry_count = listing_index->count;
  for(int i = 0; i<entry_count; i++) {
    struct zip_listing_index* entry = &listing_index->indexes[i];
    const char* ename = entry->filename;
    int name_length = entry->filename_size;
    if(name_length > min_len &&
        ename[name_length - 1] != '/' &&
        memcmp(ename, "data/", 5) == 0 &&
        memcmp(ename + 5, namespace, namespace_length) == 0 &&
        memcmp(ename + 5 + namespace_length, loc, loc_length) == 0) {
      if(result_count >= alloc_count) {
        alloc_count *= 2;
        *result = realloc(*result, alloc_count * sizeof(char**));
      }
      char* name = malloc(name_length - 5 - namespace_length + 1);
      memcpy(name, ename + 5 + namespace_length, name_length - 5 - namespace_length);
      name[name_length - 5 - namespace_length] = '\0';
      (*result)[result_count++] = name;
    }
  }

  return result_count;
}

char* namespace_file_string(const char *namespace_name, const char *file_name) {
  int namespace_len = strlen(namespace_name);
  int filename_len = strlen(file_name);

  char* lookup = malloc(5 + namespace_len + 1 + filename_len + 1);
  memcpy(lookup, "data/", 5);
  memcpy(lookup + 5, namespace_name, namespace_len);
  lookup[5 + namespace_len] = '/';
  memcpy(lookup + 6 + namespace_len, file_name, filename_len);
  lookup[5 + namespace_len + 1 + filename_len] = '\0';

  return lookup;
}

int64_t namespace_file_size(zip_t *zip, const char *namespace_name, const char *file_name) {
  char* lookup = namespace_file_string(namespace_name, file_name);
  int size = file_size(zip, lookup);
  free(lookup);
  return size;
}

char* namespace_file_content(zip_t *zip, const char *namespace_name, const char *file_name) {
  char* lookup = namespace_file_string(namespace_name, file_name);
  char* content = load_file(zip, lookup);
  free(lookup);
  return content;
}