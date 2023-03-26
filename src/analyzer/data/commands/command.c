#include "commands.h"
#include "command_ast.h"
#include "command_parser.h"
#include "../../../data_types/gamerules.h"
#include "../../namespace.h"
#include <string.h>
#include <stdio.h>

#define COMMAND_DIAGNOSTIC_RANGE(CONTEXT, TYPE, VALUE, MIN_VERSION, MAX_VERSION) \
  analyzer_add_diagnostic_range_msg_file_loc(CONTEXT->results, TYPE, VALUE, clone_string(CONTEXT->filename), CONTEXT->line_number, CONTEXT->column, MIN_VERSION, MAX_VERSION)

#define COMMAND_DIAGNOSTIC(CONTEXT, TYPE, VALUE) \
  analyzer_add_diagnostic_range_msg_file_loc(CONTEXT->results, TYPE, VALUE, clone_string(CONTEXT->filename), CONTEXT->line_number, CONTEXT->column, NULL, NULL)

#define COMMAND(NAME) command_ast_value* load_command_##NAME(struct command_load_context* context)
#define CHECK_COMMAND(NAME) if(command_length == strlen(#NAME) && memcmp(line, #NAME, command_length) == 0) { return load_command_##NAME(context); }
#define CHECK_COMMAND_ALIAS(ALIAS, NAME) if(command_length == strlen(#ALIAS) && memcmp(line, #ALIAS, command_length) == 0) { return load_command_##NAME(context); }

#define PRINT_LEN_STRING(STRING, LENGTH) \
{ \
  char* LenString = alloca(LENGTH + 1); \
  memcpy(LenString, STRING, LENGTH); \
  LenString[LENGTH] = '\0'; \
  printf("%s\n", LenString); \
}

struct command_load_context {
  const char* namespace_name;
  const char* filename;
  int line_number;
  int column;
  command_parser parser;
  struct analysis_data *data;
  struct analyzer_results *results;
};

COMMAND(advancement) {
  return NULL;
}

COMMAND(attribute) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `attribute` is not supported in this version", NULL, "20w17a");
  return NULL;
}

COMMAND(blockdata) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `blockdata` is not supported in this version, use `data block`", "17w45b", NULL);
  return NULL;
}

COMMAND(bossbar) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `bossbar` is not supported in this version", NULL, "18w05a");
  return NULL;
}

COMMAND(clear) {
  return NULL;
}

COMMAND(clone) {
  return NULL;
}

COMMAND(damage) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `damage` is not supported in this version", NULL, "23w06a");
  return NULL;
}

COMMAND(data) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `data` is not supported in this version", NULL, "17w45b");
  return NULL;
}

COMMAND(datapack) {
  return NULL;
}

COMMAND(defaultgamemode) {
  return NULL;
}

COMMAND(difficulty) {
  return NULL;
}

COMMAND(drop) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `drop` is not supported in this version", NULL, "18w43a");
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `drop` is not supported in this version, use `loot`", "18w45a", NULL);
  return NULL;
}

COMMAND(effect) {
  return NULL;
}

COMMAND(enchant) {
  return NULL;
}

COMMAND(entitydata) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `entitydata` is not supported in this version, use `data entity`", "17w45b", NULL);
  return NULL;
}

COMMAND(execute) {
  return NULL;
}

COMMAND(experience) {
  return NULL;
}

COMMAND(fill) {
  return NULL;
}

COMMAND(fillbiome) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `fillbiome` is not supported in this version", NULL, "22w46a");
  return NULL;
}

COMMAND(forceload) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `forceload` is not supported in this version", NULL, "1.14.4-pre4");
  return NULL;
}

COMMAND(function) {
  return NULL;
}

COMMAND(gamemode) {
  return NULL;
}

COMMAND(gamerule) {
  context->column = context->parser.offset + 1;
  command_ast_value_result res = command_parser_word(&context->parser);
  if(res.has_error) {
    COMMAND_DIAGNOSTIC(context, diagnostic_error, res.error_message);
    return NULL;
  }

  const struct data_type_gamerule* found_gamerule = NULL;
  for(int i = 0; i<GAMERULE_COUNT; i++) {
    const struct data_type_gamerule* gamerule = &GAMERULES[i];
    int gamerule_len = strlen(gamerule->name);
    if(res.ast.t_word.length != gamerule_len) continue;
    if(memcmp(context->parser.line + res.ast.t_word.start, gamerule->name, gamerule_len) != 0) continue;
    found_gamerule = gamerule;
    break;
  }
  if(found_gamerule == NULL) {
    COMMAND_DIAGNOSTIC(context, diagnostic_error, "Provided gamerule does not exist");
    return NULL;
  }
  if(found_gamerule->min_version != NULL) {
    COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Gamerule does not exist", found_gamerule->max_version, found_gamerule->min_version);
  }
  context->column = context->parser.offset + 1;
  if(context->parser.offset != context->parser.line_length) {
    if(found_gamerule->type == DATA_TYPE_GAMERULE_TYPE_BOOLEAN) {
      res = command_parser_boolean(&context->parser);
      if(res.has_error) {
        COMMAND_DIAGNOSTIC(context, diagnostic_error, res.error_message);
        return NULL;
      }
      if(res.ast.t_bool.in_string) {
        COMMAND_DIAGNOSTIC(context, diagnostic_info, "Write booleans without quotes");
      }
      return NULL;
    }else if(found_gamerule->type == DATA_TYPE_GAMERULE_TYPE_INTEGER) {

    }
  }

  return NULL;
}

COMMAND(give) {
  return NULL;
}

COMMAND(help) {
  return NULL;
}

COMMAND(item) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `item` is not supported in this version", NULL, "20w46a");
  return NULL;
}

COMMAND(kill) {
  return NULL;
}

COMMAND(list) {
  return NULL;
}

COMMAND(locate) {
  return NULL;
}

COMMAND(locatebiome) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `locatebiome` is not supported in this version", NULL, "20w06a");
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `locatebiome` is not supported in this version, use `locate biome`", "22w19a", NULL);
  return NULL;
}

COMMAND(loot) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `loot` is not supported in this version", NULL, "18w45a");
  return NULL;
}

COMMAND(me) {
  return NULL;
}

COMMAND(particle) {
  return NULL;
}

COMMAND(place) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `place` is not supported in this version", NULL, "22w18a");
  return NULL;
}

COMMAND(placefeature) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `placefeature` is not supported in this version", NULL, "22w03a");
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `placefeature` is not supported in this version, use `place feature`", "22w18a", NULL);
  return NULL;
}

COMMAND(playsound) {
  return NULL;
}

COMMAND(recipe) {
  return NULL;
}

COMMAND(reload) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `reload` is not supported in this version", NULL, "1.14.4-pre4");
  return NULL;
}

COMMAND(replaceitem) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `replaceitem` is not supported in this version, use `item replace`", "20w46a", NULL);
  return NULL;
}

COMMAND(ride) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `ride` is not supported in this version", NULL, "23w03a");
  return NULL;
}

COMMAND(say) {
  return NULL;
}

COMMAND(schedule) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `scnedule` is not supported in this version", NULL, "18w43a");
  return NULL;
}

COMMAND(scoreboard) {
  return NULL;
}

COMMAND(seed) {
  return NULL;
}

COMMAND(setblock) {
  return NULL;
}

COMMAND(setworldspawn) {
  return NULL;
}

COMMAND(spawnpoint) {
  return NULL;
}

COMMAND(spectate) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `spectate` is not supported in this version", NULL, "19w41a");
  return NULL;
}

COMMAND(spreadplayers) {
  return NULL;
}

COMMAND(stopsound) {
  return NULL;
}

COMMAND(summon) {
  return NULL;
}

COMMAND(tag) {
  return NULL;
}

COMMAND(team) {
  return NULL;
}

COMMAND(teammsg) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `teammsg` is not supported in this version", NULL, "19w02a");
  return NULL;
}

COMMAND(teleport) {
  return NULL;
}

COMMAND(tell) {
  return NULL;
}

COMMAND(tellraw) {
  return NULL;
}

COMMAND(time) {
  return NULL;
}

COMMAND(title) {
  return NULL;
}

COMMAND(trigger) {
  return NULL;
}

COMMAND(weather) {
  return NULL;
}

COMMAND(worldborder) {
  return NULL;
}

COMMAND(__debug_test) {
  command_ast_value_result res = command_parser_boolean(&context->parser);
  if(res.has_error) {
    printf("%s\n", res.error_message);
  }else {
    printf("Value: %d %d\n", res.ast.t_bool.value, res.ast.t_bool.in_string);
  }
  return NULL;
}

command_ast_value* load_command(struct command_load_context* context) {
  command_ast_value_result res = command_parser_word(&context->parser);
  if(res.has_error) {
    COMMAND_DIAGNOSTIC(context, diagnostic_error, res.error_message);
    return NULL;
  }

  const char* line = context->parser.line + res.ast.t_word.start;
  int command_length = res.ast.t_word.length;

  CHECK_COMMAND(__debug_test);


  CHECK_COMMAND(advancement);
  CHECK_COMMAND(attribute);
  CHECK_COMMAND(blockdata);
  CHECK_COMMAND(bossbar);
  CHECK_COMMAND(clear);
  CHECK_COMMAND(clone);
  CHECK_COMMAND(damage);
  CHECK_COMMAND(data);
  CHECK_COMMAND(datapack);
  CHECK_COMMAND(defaultgamemode);
  CHECK_COMMAND(difficulty);
  CHECK_COMMAND(drop);
  CHECK_COMMAND(effect);
  CHECK_COMMAND(enchant);
  CHECK_COMMAND(entitydata);
  CHECK_COMMAND(execute);
  CHECK_COMMAND(experience);
  CHECK_COMMAND(fill);
  CHECK_COMMAND(fillbiome);
  CHECK_COMMAND(forceload);
  CHECK_COMMAND(function);
  CHECK_COMMAND(gamemode);
  CHECK_COMMAND(gamerule);
  CHECK_COMMAND(give);
  CHECK_COMMAND(help);
  CHECK_COMMAND(item);
  CHECK_COMMAND(kill);
  CHECK_COMMAND(list);
  CHECK_COMMAND(locate);
  CHECK_COMMAND(locatebiome);
  CHECK_COMMAND(loot);
  CHECK_COMMAND(me);
  CHECK_COMMAND(particle);
  CHECK_COMMAND(place);
  CHECK_COMMAND(placefeature);
  CHECK_COMMAND(playsound);
  CHECK_COMMAND(recipe);
  CHECK_COMMAND(reload);
  CHECK_COMMAND(replaceitem);
  CHECK_COMMAND(ride);
  CHECK_COMMAND(say);
  CHECK_COMMAND(schedule);
  CHECK_COMMAND(scoreboard);
  CHECK_COMMAND(seed);
  CHECK_COMMAND(setblock);
  CHECK_COMMAND(setworldspawn);
  CHECK_COMMAND(spawnpoint);
  CHECK_COMMAND(spectate);
  CHECK_COMMAND(spreadplayers);
  CHECK_COMMAND(stopsound);
  CHECK_COMMAND(summon);
  CHECK_COMMAND(tag);
  CHECK_COMMAND(team);
  CHECK_COMMAND(teammsg);
  CHECK_COMMAND(teleport);
  CHECK_COMMAND(tell);
  CHECK_COMMAND(tellraw);
  CHECK_COMMAND(time);
  CHECK_COMMAND(title);
  CHECK_COMMAND(trigger);
  CHECK_COMMAND(weather);
  CHECK_COMMAND(worldborder);
  CHECK_COMMAND_ALIAS(tm, teammsg);
  CHECK_COMMAND_ALIAS(tp, teleport);
  CHECK_COMMAND_ALIAS(msg, tell);
  CHECK_COMMAND_ALIAS(w, tell);
  CHECK_COMMAND_ALIAS(xp, experience);

  COMMAND_DIAGNOSTIC(context, diagnostic_error, "Command is not supported");
  return NULL;
};

static void command_load(const char* namespace_name, const char* filename, int line_number, int column, const char* start, int length, struct analysis_data *data, struct analyzer_results *results) {
  char* line = alloca(length + 1);
  memcpy(line, start, length);
  line[length] = '\0';
  struct command_load_context context = {
      .namespace_name = namespace_name,
      .filename = filename,
      .line_number = line_number,
      .column = column,
      .parser = {
          .line = line,
          .line_length = length,
          .offset = column - 1
      },
      .data = data,
      .results = results,
  };
  while(context.parser.offset < context.parser.line_length && line[context.parser.offset] == ' ') {
    context.parser.offset++;
  }
  load_command(&context);
}

void load_commands(const char* namespace_name, struct zip_listing_index* index, const char* content, struct analysis_data *data, struct analyzer_results *results) {
  char* filename = alloca(index->filename_size + 1);
  memcpy(filename, index->filename, index->filename_size);
  filename[index->filename_size] = '\0';

  int max_len = strlen(content);
  int line_number = 1;
  for(int i = 0; i<max_len; i++)
  do_loop: {
    int offset = 0;
    while(i<max_len) {
      if(content[i] == ' ') {
        i++;
        offset++;
      }else {
        break;
      }
    }
    if(content[i] == '#') {
      while(i<max_len) {
        if(content[i++] == '\n') {
          line_number++;
          goto do_loop;
        }
      }
      goto do_loop;
    }
    int pre_line_number = line_number;
    int start = i - offset;
    while(i<max_len) {
      if(content[i] == '\n') {
        line_number++;
        break;
      }
      i++;
    }
    int end = i;
    if(end != start) {
      command_load(namespace_name, filename, pre_line_number, 1 + offset, content + start, end - start, data, results);
    }
  }
};