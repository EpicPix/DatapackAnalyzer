#include "zip.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "../loader.h"

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

struct zip_listing_index_list* listing_index = NULL;

static int zip_fd = 0, zip_file_mapped_length = 0;
static uint8_t* zip_file_map = NULL;

void zip_open(const char* filename) {
  zip_fd = open(filename, O_RDONLY);
  if(zip_fd < 0) {
    fprintf(stderr, "Failed to open zip\n");
    exit(1);
  }
  struct stat st;

  if(fstat(zip_fd, &st) != 0 || st.st_size < 4) {
    close(zip_fd);
    fprintf(stderr, "Failed to read zip\n");
    exit(1);
  }
  zip_file_mapped_length = st.st_size;

  uint8_t* mapped_file = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, zip_fd, 0);
  zip_file_map = mapped_file;
  if(read_value_32(mapped_file, 0, st.st_size) != 0x04034b50) {
    zip_close();
    fprintf(stderr, "Invalid zip header\n");
    exit(1);
  }


  int result_count = 0;
  int alloc_count = 8;
  listing_index = malloc(sizeof(struct zip_listing_index_list) + alloc_count * sizeof(struct zip_listing_index));
  int offset = 0;

  uint32_t header = read_value_32(mapped_file, offset + 0, st.st_size);
  while(header != 0x06054b50) {
    if(header == 0x04034b50) {
      uint16_t gp = read_value_16(mapped_file, offset + 6, st.st_size);
      uint32_t compressed_size = read_value_32(mapped_file, offset + 18, st.st_size);
      uint32_t decompressed_size = read_value_32(mapped_file, offset + 22, st.st_size);
      uint32_t filename_length = read_value_16(mapped_file, offset + 26, st.st_size);
      uint32_t extra_length = read_value_16(mapped_file, offset + 28, st.st_size);
      uint16_t compression = read_value_16(mapped_file, offset + 8, st.st_size);
      void* data_location = mapped_file + offset + 30 + filename_length + extra_length;

      if(result_count >= alloc_count) {
        alloc_count *= 2;
        listing_index = realloc(listing_index, sizeof(struct zip_listing_index_list) + alloc_count * sizeof(struct zip_listing_index));
      }
      struct zip_listing_index* entry = &listing_index->indexes[result_count++];
      entry->size = decompressed_size;
      entry->compressed_size = decompressed_size;
      entry->compressed_data = data_location;
      entry->decompressed_data = NULL;
      entry->filename = (const char*) (mapped_file + offset + 30);
      entry->filename_size = filename_length;
      entry->flags = compression;

      offset += 30 + filename_length + extra_length + compressed_size + (gp & 8 ? 12 : 0);
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

  listing_index->count = result_count;
}

void zip_close() {
  if(listing_index) {
    for(int i = 0; i < listing_index->count; i++) {
      if(listing_index->indexes[i].decompressed_data) {
        free(listing_index->indexes[i].decompressed_data);
      }
    }
    free(listing_index);
  }
  munmap(zip_file_map, zip_file_mapped_length);
  close(zip_fd);
  zip_file_map = NULL;
  zip_file_mapped_length = 0;
  zip_fd = 0;
}