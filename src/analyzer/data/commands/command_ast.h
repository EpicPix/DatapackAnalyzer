#pragma once

typedef enum command_ast_type {
  COMMAND_AST_TYPE_WORD = 0,
} command_ast_type;

struct command_ast_word {
  int start;
  int length;
};

typedef struct command_ast {
  command_ast_type type;
  union {
    struct command_ast_word word;
  } data;
} command_ast;
