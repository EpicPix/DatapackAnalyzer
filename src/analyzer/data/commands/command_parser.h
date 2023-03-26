#pragma once
#include "command_ast.h"
#include <stdbool.h>

typedef struct command_parser {
  const char* line;
  int line_length;
  int offset;
} command_parser;

typedef struct command_ast_value_result {
  union {
    const char* error_message;
    struct command_ast_value ast;
  };
  bool has_error;
} command_ast_value_result;

#define COMMAND_AST_ERROR(MESSAGE) ((command_ast_value_result) { .has_error = true, .error_message = (MESSAGE) })
#define COMMAND_AST_WORD(START, LENGTH) ((command_ast_value_result) { .has_error = false, .ast = { .type = COMMAND_AST_VALUE_TYPE_WORD, .t_word = { .start = START, .length = LENGTH } } })
#define COMMAND_AST_IDENTIFIER(NSTART, NLENGTH, ISTART, ILENGTH) ((command_ast_value_result) { .has_error = false, .ast = { .type = COMMAND_AST_VALUE_TYPE_IDENTIFIER, .t_identifier = { .namespace_start = NSTART, .namespace_length = NLENGTH, .identifier_start = ISTART, .identifier_length = ILENGTH } } })
#define COMMAND_AST_BOOLEAN(START, LENGTH, VALUE) ((command_ast_value_result) { .has_error = false, .ast = { .type = COMMAND_AST_VALUE_TYPE_BOOL, .t_bool = { .start = START, .length = LENGTH, .value = VALUE } } })
#define COMMAND_AST_INTEGER(START, LENGTH, VALUE) ((command_ast_value_result) { .has_error = false, .ast = { .type = COMMAND_AST_VALUE_TYPE_INTEGER, .t_int = { .start = START, .length = LENGTH, .value = VALUE } } })
#define COMMAND_AST_LONG(START, LENGTH, VALUE) ((command_ast_value_result) { .has_error = false, .ast = { .type = COMMAND_AST_VALUE_TYPE_LONG, .t_long = { .start = START, .length = LENGTH, .value = VALUE } } })

command_ast_value_result command_parser_word(command_parser* parser);
command_ast_value_result command_parser_identifier(command_parser* parser);
command_ast_value_result command_parser_boolean(command_parser* parser);