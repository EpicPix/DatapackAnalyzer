#include "loader.h"
#include <stdlib.h>
#include <zip.h>

char *load_file(zip_t *zip, const char *file_path) {
  zip_stat_t stat;
  int result = zip_stat(zip, file_path, 0, &stat);
  if (result)
    return NULL;

  zip_file_t *file = zip_fopen(zip, file_path, 0);
  char *content = malloc(stat.size + 1);
  zip_fread(file, content, stat.size);
  content[stat.size] = '\0';
  zip_fclose(file);
  return content;
}
