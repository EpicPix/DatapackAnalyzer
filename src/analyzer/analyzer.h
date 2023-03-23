#pragma once

#include "../versions.h"
#include <zip.h>

struct analyzer_results {
  struct diagnostics_info *diagnostics;
  int diagnostics_count;
  int diagnostics_alloc;
};

struct analyzer_results *analyze_datapack(zip_t *zip);

