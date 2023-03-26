#include "command_parser.h"

command_ast_result command_parser_word(command_parser* parser) {
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

command_ast_result command_parser_identifier(command_parser* parser) {
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