#include "commands.h"
#include "../../namespace.h"
#include <string.h>

#define COMMAND_DIAGNOSTIC_RANGE(CONTEXT, TYPE, VALUE, MIN_VERSION, MAX_VERSION) \
  analyzer_add_diagnostic_range_msg_file_loc(CONTEXT->results, TYPE, VALUE, namespace_file_string(CONTEXT->namespace_name, context->filename + 1), context->line_number, context->column, MIN_VERSION, MAX_VERSION)

#define COMMAND_DIAGNOSTIC(CONTEXT, TYPE, VALUE) \
  analyzer_add_diagnostic_range_msg_file_loc(CONTEXT->results, TYPE, VALUE, namespace_file_string(CONTEXT->namespace_name, context->filename + 1), context->line_number, context->column, NULL, NULL)

#define COMMAND(NAME) void load_command_##NAME(zip_t* zip, struct command_load_context* context)
#define CHECK_COMMAND(NAME) if(command_length == strlen(#NAME) && memcmp(line, #NAME, command_length) == 0) { load_command_##NAME(zip, context); return; }
#define CHECK_COMMAND_ALIAS(ALIAS, NAME) if(command_length == strlen(#ALIAS) && memcmp(line, #ALIAS, command_length) == 0) { load_command_##NAME(zip, context); return; }

struct command_load_context {
  const char* namespace_name;
  const char* filename;
  int line_number;
  int column;
  const char* line;
  int line_length;
  struct analysis_data *data;
  struct analyzer_results *results;
};

COMMAND(advancement) {

}

COMMAND(attribute) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `attribute` is not supported in this version", NULL, "20w17a");
}

COMMAND(blockdata) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `blockdata` is not supported in this version, use `data block`", "17w45b", NULL);
}

COMMAND(bossbar) {

}

COMMAND(clear) {

}

COMMAND(clone) {

}

COMMAND(damage) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `damage` is not supported in this version", NULL, "23w06a");
}

COMMAND(data) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `data` is not supported in this version", NULL, "17w45b");
}

COMMAND(datapack) {

}

COMMAND(defaultgamemode) {

}

COMMAND(difficulty) {

}

COMMAND(effect) {

}

COMMAND(enchant) {

}

COMMAND(entitydata) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `entitydata` is not supported in this version, use `data entity`", "17w45b", NULL);
}

COMMAND(execute) {

}

COMMAND(experience) {

}

COMMAND(fill) {

}

COMMAND(fillbiome) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `fillbiome` is not supported in this version", NULL, "22w46a");
}

COMMAND(forceload) {

}

COMMAND(function) {

}

COMMAND(gamemode) {

}

COMMAND(gamerule) {

}

COMMAND(give) {

}

COMMAND(help) {

}

COMMAND(item) {

}

COMMAND(kill) {

}

COMMAND(list) {

}

COMMAND(locate) {

}

COMMAND(locatebiome) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `locatebiome` is not supported in this version", NULL, "20w06a");
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `locatebiome` is not supported in this version, use `locate biome`", "22w19a", NULL);
}

COMMAND(loot) {

}

COMMAND(me) {

}

COMMAND(particle) {

}

COMMAND(place) {

}

COMMAND(placefeature) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `placefeature` is not supported in this version", NULL, "22w03a");
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `placefeature` is not supported in this version, use `place feature`", "22w18a", NULL);
}

COMMAND(playsound) {

}

COMMAND(recipe) {

}

COMMAND(reload) {

}

COMMAND(replaceitem) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `replaceitem` is not supported in this version, use `item replace`", "20w46a", NULL);
}

COMMAND(ride) {
  COMMAND_DIAGNOSTIC_RANGE(context, diagnostic_error, "Command `ride` is not supported in this version", NULL, "23w03a");
}

COMMAND(say) {

}

COMMAND(schedule) {

}

COMMAND(scoreboard) {

}

COMMAND(seed) {

}

COMMAND(setblock) {

}

COMMAND(setworldspawn) {

}

COMMAND(spawnpoint) {

}

COMMAND(spectate) {

}

COMMAND(spreadplayers) {

}

COMMAND(stopsound) {

}

COMMAND(summon) {

}

COMMAND(tag) {

}

COMMAND(team) {

}

COMMAND(teammsg) {

}

COMMAND(teleport) {

}

COMMAND(tell) {

}

COMMAND(tellraw) {

}

COMMAND(time) {

}

COMMAND(title) {

}

COMMAND(trigger) {

}

COMMAND(weather) {

}

COMMAND(whitelist) {

}

COMMAND(worldborder) {

}

void load_command(zip_t* zip, struct command_load_context* context) {
  struct analyzer_results *results = context->results;
  const char* line = context->line;

  int command_length = 0;
  while(command_length < context->line_length) {
    char c = line[command_length];
    if(c == ' ' || c == '\t') {
      break;
    }
    command_length++;
  }

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
  CHECK_COMMAND(whitelist);
  CHECK_COMMAND(worldborder);
  CHECK_COMMAND_ALIAS(tm, teammsg);
  CHECK_COMMAND_ALIAS(tp, teleport);
  CHECK_COMMAND_ALIAS(msg, tell);
  CHECK_COMMAND_ALIAS(w, tell);
  CHECK_COMMAND_ALIAS(xp, experience);

  COMMAND_DIAGNOSTIC(context, diagnostic_error, "Command is not supported");
};

void load_commands(zip_t* zip, const char* namespace_name, const char* filename, char* content, struct analysis_data *data, struct analyzer_results *results) {
  int max_len = strlen(content);
  int line_number = 1;
  for(int i = 0; i<max_len; i++) {
  do_loop:
    if(content[i] == '#') {
      while(i<max_len) {
        if(content[i++] == '\n') {
          line_number++;
          break;
        }
      }
      goto do_loop;
    }
    int start = i;
    while(i<max_len) {
      if(content[i++] == '\n') {
        line_number++;
        goto do_loop;
      }
    }
    int end = i;
    if(end != start) {
      char endChar = content[end];
      content[end] = '\0';
      struct command_load_context context = {
          .namespace_name = namespace_name,
          .filename = filename,
          .line_number = line_number,
          .column = 1,
          .line = content + start,
          .line_length = end - start,
          .data = data,
          .results = results,
      };
      load_command(zip, &context);
      content[end] = endChar;
    }
  }
};