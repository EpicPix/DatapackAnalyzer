#pragma once

typedef enum command_ast_type {
  COMMAND_AST_TYPE_WORD = 0,
} command_ast_type;

typedef struct command_ast {
  command_ast_type type;
} command_ast;