#include "command_parser.h"

command_ast_result command_parser_word(command_parser* parser) {
  const char* line = parser->line;

  int length = 0;
  int start = parser->offset;
  while(parser->offset < parser->line_length) {
    char c = line[parser->offset];
    if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '-' || c == '.' || c == '+')) {
      if(length != 0) {
        if(line[parser->offset] != ' ') {
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