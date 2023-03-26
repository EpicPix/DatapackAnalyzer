#pragma once
#include "command_ast.h"
#include <stdbool.h>

typedef struct command_parser {
  const char* line;
  int line_length;
  int offset;
} command_parser;

typedef struct command_ast_result {
  union {
    const char* error_message;
    struct command_ast ast;
  };
  bool has_error;
} command_ast_result;

#define COMMAND_AST_ERROR(MESSAGE) ((command_ast_result) { .has_error = true, .error_message = (MESSAGE) })
#define COMMAND_AST_WORD(START, LENGTH) ((command_ast_result) { .has_error = false, .ast = { .type = COMMAND_AST_TYPE_WORD, .data = { .word = { .start = START, .length = LENGTH } } } })
#define COMMAND_AST_IDENTIFIER(NSTART, NLENGTH, ISTART, ILENGTH) ((command_ast_result) { .has_error = false, .ast = { .type = COMMAND_AST_TYPE_IDENTIFIER, .data = { .identifier = { .namespace_start = NSTART, .namespace_length = NLENGTH, .identifier_start = ISTART, .identifier_length = ILENGTH } } } })

command_ast_result command_parser_word(command_parser* parser);
command_ast_result command_parser_identifier(command_parser* parser);