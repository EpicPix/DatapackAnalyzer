#include "command_parser.h"
#include <string.h>

command_ast_value_result command_parser_word(command_parser* parser) {
  const char* line = parser->line;

  int length = 0;
  int start = parser->offset;
  while(parser->offset < parser->line_length) {
    char c = line[parser->offset];
    if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '-' || c == '.' || c == '+')) {
      if(length != 0) {
        if(c != ' ') {
          return COMMAND_AST_ERROR("Expected space after word");
        }
        parser->offset++;
      }
      break;
    }
    parser->offset++;
    length++;
  }
  if(length == 0) {
    return COMMAND_AST_ERROR("Read empty word");
  }

  return COMMAND_AST_WORD(start, length);
}

command_ast_value_result command_parser_identifier(command_parser* parser) {
  const char* line = parser->line;

  int namespace_length = 0;
  int namespace_start = -1;

  int length = 0;
  int start = parser->offset;

  bool hasSlashes = false;
  while(parser->offset < parser->line_length) {
    char c = line[parser->offset];
    if(!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_' || c == ':' || c == '/' || c == '.' || c == '-')) {
      if(length != 0) {
        if(c != ' ') {
          return COMMAND_AST_ERROR("Expected space after identifier");
        }
        parser->offset++;
      }
      break;
    }
    if(c == '/') hasSlashes = true;
    if(c == ':') {
      if(namespace_start == -1) {
        if(hasSlashes) {
          return COMMAND_AST_ERROR("Identifier path cannot have slashes");
        }
        namespace_start = start;
        namespace_length = length;
        start = parser->offset+1;
        length = 0;
      }else {
        return COMMAND_AST_ERROR("Invalid identifier, expected `namespace:location` or `location`");
      }
    }
    parser->offset++;
    length++;
  }
  if(namespace_start != -1 && namespace_length == 0) {
    return COMMAND_AST_ERROR("Namespace cannot be empty when `:` is present");
  }
  if(length == 0) {
    return COMMAND_AST_ERROR("Expected a location in resource location");
  }

  return COMMAND_AST_IDENTIFIER(namespace_start, namespace_length, start, length);
}

command_ast_value_result command_parser_boolean(command_parser* parser) {
  const char* line = parser->line;

  if(parser->offset > parser->line_length) {
    return COMMAND_AST_ERROR("Reached end of line before input");
  }

  if(line[parser->offset] == '"' || line[parser->offset] == '\'') {
    command_ast_value_result res = command_parser_string(parser);
    if(res.has_error) return res;
    if(res.ast.t_string.length == 4) {
      if(memcmp(line + res.ast.t_string.start, "true", 4) == 0) {
        return COMMAND_AST_BOOLEAN(res.ast.t_string.start, res.ast.t_string.length, true, true);
      }
    }else if(res.ast.t_string.length == 5) {
      if(memcmp(line + res.ast.t_string.start, "false", 5) == 0) {
        return COMMAND_AST_BOOLEAN(res.ast.t_string.start, res.ast.t_string.length, false, true);
      }
    }
    goto error;
  }

  int start = parser->offset;
  if(line[start] == 'f') {
    if(parser->offset + 5 > parser->line_length) {
      goto error;
    }
    if(line[start+1] != 'a' || line[start+2] != 'l' || line[start+3] != 's' || line[start+4] != 'e') {
      goto error;
    }
    parser->offset += 5;
    if(parser->offset < parser->line_length) {
      if(line[parser->offset++] != ' ') {
        goto error;
      }
    }
    return COMMAND_AST_BOOLEAN(start, start + 5, false, false);
  }else if(line[start] == 't') {
    if(parser->offset + 4 > parser->line_length) {
      goto error;
    }
    if(line[start+1] != 'r' || line[start+2] != 'u' || line[start+3] != 'e') {
      goto error;
    }
    parser->offset += 4;
    if(parser->offset < parser->line_length) {
      if(line[parser->offset++] != ' ') {
        goto error;
      }
    }
    return COMMAND_AST_BOOLEAN(start, start + 4, true, false);
  }

error:
  return COMMAND_AST_ERROR("Invalid boolean");
}

command_ast_value_result command_parser_string(command_parser* parser) {
  const char* line = parser->line;
  if(parser->offset > parser->line_length) {
    return COMMAND_AST_ERROR("String end of line");
  }
  if(line[parser->offset] != '"' && line[parser->offset] != '\'') {
    command_ast_value_result res = command_parser_word(parser);
    if(res.has_error) return res;
    return COMMAND_AST_STRING(res.ast.t_word.start, res.ast.t_word.length);
  }
  char end_char = line[parser->offset];
  parser->offset++;
  int start = parser->offset;
  bool escape_seq = false;
  while(parser->offset < parser->line_length) {
    if(line[parser->offset] == '\\') {
      escape_seq = true;
    }else if(escape_seq) {
      if(line[parser->offset] != end_char) {
        return COMMAND_AST_ERROR("Invalid string escape sequence");
      }
      escape_seq = false;
    }else if(line[parser->offset] == end_char) {
      int end = parser->offset;
      parser->offset++;
      return COMMAND_AST_STRING(start, end - start);
    }
    parser->offset++;
  }
  return COMMAND_AST_ERROR("String reached end of line before end quote");
}