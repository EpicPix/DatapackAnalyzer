#include <stdint.h>
#include "../loader.h"

int list_namespaces(char ***result);

int list_namespace_files(const char* namespace_name, char* loc, struct zip_listing_index ***result);
#define list_namespace_files_foreach(namespace_name, loc, exec...) \
{ \
  struct zip_listing_index** res; \
  int count = list_namespace_files(namespace_name, loc, &res); \
  for(int i = 0; i<count; i++) { \
    struct zip_listing_index* entry = res[i]; \
    exec; \
  } \
  free(res); \
}

#define namespace_file_exists(namespace_name, file_name) (namespace_file_size(namespace_name, file_name) != -1)

char* namespace_file_string(const char *namespace_name, const char *file_name);
int64_t namespace_file_size(const char *namespace_name, const char *file_name);
char* namespace_file_content(const char *namespace_name, const char *file_name);