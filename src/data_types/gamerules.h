#pragma once

enum data_type_gamerule_type {
  DATA_TYPE_GAMERULE_TYPE_BOOLEAN = 0,
  DATA_TYPE_GAMERULE_TYPE_INTEGER = 1,
};

struct data_type_gamerule {
  enum data_type_gamerule_type type;
  const char* name;
  const char* min_version;
  const char* max_version;
};

extern const struct data_type_gamerule GAMERULES[];
extern const int GAMERULE_COUNT;
