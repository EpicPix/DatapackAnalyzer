#pragma once

#include "../analyzer_diagnostics.h"
#include "../../loader.h"

struct analysis_data {

};

void load_advancements(const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_chat_types(const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_damage_types(const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_functions(const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_item_modifiers(const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_loot_tables(const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_predicates(const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_recipes(const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_structures(const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_tags(const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
void load_worldgens(const char* namespace_name, struct analysis_data *data, struct analyzer_results *results);
