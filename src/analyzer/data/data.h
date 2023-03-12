#pragma once

#include <zip.h>
#include "../analyzer_diagnostics.h"

struct analysis_data {

};

void load_advancements(zip_t* zip, const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_chat_type(zip_t* zip, const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_damage_type(zip_t* zip, const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_functions(zip_t* zip, const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_item_modifiers(zip_t* zip, const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_loot_tables(zip_t* zip, const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_predicates(zip_t* zip, const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_recipes(zip_t* zip, const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_structures(zip_t* zip, const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_tags(zip_t* zip, const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_worldgen(zip_t* zip, const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
