#include <json-c/json.h>
#include <stdint.h>
#include <stdio.h>
#include <zip.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage; %s <datapack>\n", argv[0]);
    return 1;
  }
  zip_t *zip = zip_open(argv[1], ZIP_RDONLY, NULL);
  if (!zip)
    return 1;

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

  zip_close(zip);
  return 0;
}