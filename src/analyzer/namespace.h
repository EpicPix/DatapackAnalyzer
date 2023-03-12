#include <stdint.h>
#include <zip.h>

int list_namespaces(zip_t *zip, char ***result);

int list_namespace_files(zip_t *zip, const char* namespace_name, char* loc, char ***result);
#define list_namespace_files_foreach(zip, namespace_name, loc, exec...) \
{ \
  char** res; \
  int count = list_namespace_files(zip, namespace_name, loc, &res); \
  for(int i = 0; i<count; i++) { \
    char* filename = res[i]; \
    exec; \
    free(res[i]); \
  } \
  free(res); \
}

#define namespace_file_exists(zip, namespace_name, file_name) (namespace_file_size(zip, namespace_name, file_name) != -1)

char* namespace_file_string(const char *namespace_name, const char *file_name);
int64_t namespace_file_size(zip_t *zip, const char *namespace_name, const char *file_name);
char* namespace_file_content(zip_t *zip, const char *namespace_name, const char *file_name);