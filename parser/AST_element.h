#ifndef AST_element_H
#define AST_element_H

#include <list>
#include <string>
#include <iterator>

#include "../tokenisation/tokenisation.h"

class AST_element{
public:
    token primary_token;
    std::list<AST_element> depend_tokens;

    AST_element(token token);

    AST_element();

    void add_depend(AST_element depend);

    std::list<AST_element>::iterator get_iterator();

    std::string to_string();

    void pop_depend();

    AST_element get_last_depend();
};

#endif