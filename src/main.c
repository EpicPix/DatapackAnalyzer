#include <json-c/json.h>
#include <stdio.h>
#include <zip.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage; %s <datapack>\n", argv[0]);
    return 1;
  }
  printf("Hello world! %s\n", argv[1]);
  zip_t *zip = zip_open(argv[1], ZIP_RDONLY, NULL);
  printf("ZIP: %p\n", zip);
  return 0;
}