#pragma once
#include "../data.h"
#include <zip.h>

void load_commands(zip_t* zip, const char* namespace_name, const char* filename, const char* content, struct analysis_data *data, struct analyzer_results *results);