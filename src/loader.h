#include <json-c/json.h>
#include <zip.h>

char *load_file(zip_t *zip, const char *file);
json_object *get_file_json(zip_t *zip, const char *filename);
int get_pack_format(zip_t *zip);
