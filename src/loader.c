#include "loader.h"
#include <stdlib.h>
#include <zip.h>

void load_files(zip_t *zip) {
  int64_t entry_count = zip_get_num_entries(zip, 0);
  for (int64_t i = 0; i < entry_count; i++) {
    zip_stat_t stat;
    zip_stat_index(zip, i, 0, &stat);
    zip_file_t *file = zip_fopen_index(zip, i, 0);
    char *content = malloc(stat.size + 1);
    zip_fread(file, content, stat.size);
    content[stat.size] = '\0';
    free(content);
  }
}