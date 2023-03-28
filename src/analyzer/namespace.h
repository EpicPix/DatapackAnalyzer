#include <stdint.h>
#include "../loader.h"

int list_namespaces(struct zip_listing_index ***result);

int list_namespace_files(struct zip_listing_index* namespace_index, char* loc, struct zip_listing_index ***result);
#define list_namespace_files_foreach(namespace_index, loc, exec...) \
{ \
  struct zip_listing_index** res; \
  int count = list_namespace_files(namespace_index, loc, &res); \
  for(int i = 0; i<count; i++) { \
    struct zip_listing_index* entry = res[i]; \
    exec; \
  } \
  FREE(res); \
}

void namespace_file_string_buf(const char *namespace_name, const char *file_name, char* buffer);
char* namespace_file_string(const char *namespace_name, const char *file_name);
struct zip_listing_index* namespace_file_index(const char *namespace_name, const char *file_name);
struct zip_listing_index* namespace_file_index_by_index(struct zip_listing_index* namespace, const char *file_name);