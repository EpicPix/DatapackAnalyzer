#include "namespace.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int list_namespaces(zip_t *zip, char ***result) {
  int result_count = 0;
  int alloc_count = 8;
  *result = malloc(alloc_count * sizeof(char**));

  int entry_count = zip_get_num_entries(zip, 0);
  for(int i = 0; i<entry_count; i++) {
    zip_stat_t stat;
    zip_stat_index(zip, i, 0, &stat);
    int name_length = strlen(stat.name);
    if(name_length > 5 && stat.name[name_length - 1] == '/' && strncmp(stat.name, "data/", 5) == 0) {
      bool valid = true;
      for(int j = 5; j<name_length - 1; j++) {
        if(stat.name[j] == '/') {
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
        memcpy(namespace_name, stat.name + 5, name_length - 6);
        namespace_name[name_length - 6] = '\0';
        (*result)[result_count++] = namespace_name;
      }
    }
  }

  return result_count;
}