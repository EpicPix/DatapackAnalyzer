#include <stdint.h>
#include "../loader.h"

typedef void(listing_foreach_function)(struct zip_listing_index*, void*);

void list_namespaces_foreach(listing_foreach_function* foreach_callback, void* args);
void list_namespace_files_foreach(struct zip_listing_index* namespace_index, char* loc, listing_foreach_function* foreach_callback, void* args);

void namespace_file_string_buf(const char *namespace_name, const char *file_name, char* buffer);
char* namespace_file_string(const char *namespace_name, const char *file_name);
struct zip_listing_index* namespace_file_index(const char *namespace_name, const char *file_name);
struct zip_listing_index* namespace_file_index_by_index(struct zip_listing_index* namespace, const char *file_name);