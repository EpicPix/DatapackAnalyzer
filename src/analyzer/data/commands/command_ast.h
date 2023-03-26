#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum command_ast_value_type {
  COMMAND_AST_VALUE_TYPE_WORD = 0,
  COMMAND_AST_VALUE_TYPE_IDENTIFIER = 1,
  COMMAND_AST_VALUE_TYPE_BOOL = 2,
  COMMAND_AST_VALUE_TYPE_INTEGER = 3,
  COMMAND_AST_VALUE_TYPE_LONG = 4,
  COMMAND_AST_VALUE_TYPE_STRING = 5,
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

struct command_ast_value_bool {
  int start;
  int length;
  bool value;
  bool in_string;
};

struct command_ast_value_integer {
  int start;
  int length;
  int32_t value;
};

struct command_ast_value_long {
  int start;
  int length;
  int64_t value;
};

struct command_ast_value_string {
  int start;
  int length;
};

typedef struct command_ast_value {
  union {
    struct command_ast_value_word t_word;
    struct command_ast_value_identifier t_identifier;
    struct command_ast_value_bool t_bool;
    struct command_ast_value_integer t_int;
    struct command_ast_value_long t_long;
    struct command_ast_value_string t_string;
  };
  command_ast_value_type type;
} command_ast_value;
