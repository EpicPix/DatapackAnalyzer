#pragma once

typedef enum command_ast_type {
  COMMAND_AST_TYPE_WORD = 0,
  COMMAND_AST_TYPE_IDENTIFIER = 0,
} command_ast_type;

struct command_ast_word {
  int start;
  int length;
};

struct command_ast_identifier {
  int namespace_start;
  int namespace_length;
  int identifier_start;
  int identifier_length;
};

typedef struct command_ast {
  union {
    struct command_ast_word word;
    struct command_ast_identifier identifier;
  } data;
  command_ast_type type;
} command_ast;
