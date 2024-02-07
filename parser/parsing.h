#ifndef PARSER_H
#define PARSER_H

#include "../tokenisation/tokenisation.h"
#include "AST_element.h"
#include "scope.h"

class Parser{
    list_of_token tokens;
    unsigned current = 0;
    bool parse_ended = false;

public:
    Parser(list_of_token);

    AST_element parse();

private:
    bool is_parsed();

    AST_element match_token(token_type type);

    void expression(AST_element& context);
};

#endif