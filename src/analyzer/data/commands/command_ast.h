#pragma once

typedef enum command_ast_value_type {
  COMMAND_AST_VALUE_TYPE_WORD = 0,
  COMMAND_AST_VALUE_TYPE_IDENTIFIER = 0,
} command_ast_value_type;

struct command_ast_value_word {
  int start;
  int length;
};

struct command_ast_value_identifier {
  int namespace_start;
  int namespace_length;
  int identifier_start;
  int identifier_length;
};

typedef struct command_ast_value {
  union {
    struct command_ast_value_word word;
    struct command_ast_value_identifier identifier;
  } data;
  command_ast_value_type type;
} command_ast_value;
