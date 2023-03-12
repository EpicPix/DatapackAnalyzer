#include <zip.h>

struct diagnostics_source_info {
  const char* filename;
  int line;
  int column;
};

struct diagnostics_info {
  int type;
  struct diagnostics_source_info source;
};

struct datapack_results {
  const char *version;
  struct diagnostics_info** diagnostics;
  int diagnostics_count;
};

struct analyzer_results {
  int version_count;
  struct datapack_results *version_results;
};

struct analyzer_results *analyze_datapack(zip_t *zip);