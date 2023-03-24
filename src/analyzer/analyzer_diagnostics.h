#pragma once

#include "diagnostics.h"
#include "analyzer.h"

enum diagnostic_type;

void analyzer_add_diagnostic_range_msg_file_loc(struct analyzer_results *results, enum diagnostic_type type, const char* message, char* file, int line, int column, const char* min_version, const char* max_version);
void analyzer_add_diagnostic_range_msg_file(struct analyzer_results *results, enum diagnostic_type type, const char* message, char* file, const char* min_version, const char* max_version);
void analyzer_add_diagnostic_range_msg(struct analyzer_results *results, enum diagnostic_type type, const char* message, const char* min_version, const char* max_version);
