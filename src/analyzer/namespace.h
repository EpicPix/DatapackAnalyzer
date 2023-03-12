#include <stdint.h>
#include <zip.h>

int list_namespaces(zip_t *zip, char ***result);

char* namespace_file_string(const char *namespace_name, const char *file_name);
int64_t namespace_file_size(zip_t *zip, const char *namespace_name, const char *file_name);
char* namespace_file_content(zip_t *zip, const char *namespace_name, const char *file_name);