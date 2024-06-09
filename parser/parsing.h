#ifndef PARSER_H
#define PARSER_H

#include <iterator>
#include <iostream>

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
    token get_current();
    token get_next();

    AST_element match_token(token_type type);
    AST_element match_token_data(std::string data);

    void simple_expression(AST_element& context);
    void expression(AST_element& context);
    void assignment(AST_element& context);
    void function_declaration(AST_element& context);

    AST_element parse_value();
};

#endif