#include "zip.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

static inline void read_value_valid(uint32_t index, uint32_t max) {
  if(index >= max) {
    fprintf(stderr, "Invalid read [%d] from max length [%d]", index, max);
    exit(1);
  }
}

static inline uint8_t read_value_8(uint8_t* bytes, uint32_t index, uint32_t max) {
  read_value_valid(index, max);
  return bytes[index];
}

static inline uint16_t read_value_16(uint8_t* bytes, uint32_t index, uint32_t max) {
  read_value_valid(index + 1, max);
  return bytes[index] | (bytes[index + 1] << 8);
}

static inline uint32_t read_value_32(uint8_t* bytes, uint32_t index, uint32_t max) {
  read_value_valid(index + 3, max);
  return bytes[index] | (bytes[index + 1] << 8) | (bytes[index + 2] << 16) | (bytes[index + 3] << 24);
}

void zip_file_open(const char* filename) {
  int fd = open(filename, O_RDONLY);
  if(fd < 0)
    return;
  struct stat st;

  if(fstat(fd, &st) != 0 || st.st_size < 30) {
    close(fd);
    return;
  }

  uint8_t* mapped_file = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if(read_value_32(mapped_file, 0, st.st_size) != 0x04034b50) {
    fprintf(stderr, "Invalid zip header\n");
    return;
  }
  int offset = 0;

  uint32_t header = read_value_32(mapped_file, offset + 0, st.st_size);
  while(header != 0x06054b50) {
    if(header == 0x04034b50) {
      uint16_t gp = read_value_16(mapped_file, offset + 6, st.st_size);
      uint32_t compressed_size = read_value_32(mapped_file, offset + 18, st.st_size);
//      uint32_t decompressed_size = read_value_32(mapped_file, offset + 22, st.st_size);
      uint32_t filename_length = read_value_16(mapped_file, offset + 26, st.st_size);
      uint32_t extra_length = read_value_16(mapped_file, offset + 28, st.st_size);
      char* filename_value = alloca(filename_length + 1); // debug stuff
      memcpy(filename_value, mapped_file + offset + 30, filename_length);
      filename_value[filename_length] = '\0';
      printf("%s\n", filename_value);
//      uint16_t compression = read_value_16(mapped_file, offset + 8, st.st_size);
//      void* data_location = mapped_file + offset + 30 + filename_length + extra_length;
//      if(!compression) {
//        char* content_value = alloca(compressed_size + 1); // debug stuff
//        memcpy(content_value, data_location, compressed_size);
//        content_value[compressed_size] = '\0';
//        printf("%s", content_value);
//      }else {
//        void* decompressed_data = calloc(decompressed_size, 1);
//      }




      offset += 30 + filename_length + extra_length + compressed_size + (gp & 8 ? 12 : 0);
//      printf("%d\n", gp);
    }else if(header == 0x02014b50) {
      uint32_t filename_length = read_value_16(mapped_file, offset + 28, st.st_size);
      uint32_t extra_length = read_value_16(mapped_file, offset + 30, st.st_size);
      uint32_t comment_length = read_value_16(mapped_file, offset + 32, st.st_size);
      offset += 46 + filename_length + extra_length + comment_length;
    }else {
      printf("Unknown ZIP header: %08x\n", header);
      exit(1);
    }
    header = read_value_32(mapped_file, offset + 0, st.st_size);
  }
}