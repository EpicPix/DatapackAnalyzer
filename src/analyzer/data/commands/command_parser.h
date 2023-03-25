#pragma once
#include "command_ast.h"

typedef struct command_parser {
  const char* line;
  int line_length;
  int offset;
} *command_parser;

command_ast command_parser_word(command_parser parser);