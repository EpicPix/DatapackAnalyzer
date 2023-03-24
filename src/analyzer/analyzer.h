#pragma once

#include "../versions.h"

struct analyzer_results {
  struct diagnostics_info *diagnostics;
  int diagnostics_count;
  int diagnostics_alloc;
};

struct analyzer_results *analyze_datapack();

