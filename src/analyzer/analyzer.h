#pragma once

#include "../versions.h"
#include <zip.h>

struct datapack_results {
  const struct version_info *version;
  struct diagnostics_info *diagnostics;
  int diagnostics_count;
  int diagnostics_alloc;
};

struct analyzer_results {
  int version_count;
  struct datapack_results *version_results;
};

struct analyzer_results *analyze_datapack(zip_t *zip, const struct version_info* specific_version);

