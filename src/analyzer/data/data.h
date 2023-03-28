#pragma once

#include "../analyzer_diagnostics.h"
#include "../../loader.h"

struct analysis_data {

};

void load_advancements(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results);
void load_chat_types(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results);
void load_damage_types(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results);
void load_functions(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results);
void load_item_modifiers(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results);
void load_loot_tables(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results);
void load_predicates(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results);
void load_recipes(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results);
void load_structures(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results);
void load_tags(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results);
void load_worldgens(struct zip_listing_index* namespace_index, struct analysis_data *data, struct analyzer_results *results);
