#ifndef AST_element_H
#define AST_element_H

#include <list>
#include <string>
#include <iterator>
#include <ostream>

#include "../tokenisation/tokenisation.h"
#include "scope.h"

class AST_element{
public:
    token primary_token;
    std::list<AST_element> depend_tokens;
    Scope* scope = nullptr;

    AST_element(token token);

    AST_element();

    void add_depend(AST_element depend);

    std::list<AST_element>::iterator get_iterator();

    void output(std::ostream &output);

    void pop_depend();

    AST_element get_last_depend();

    void create_scope();

    Scope* get_scope();

    ~AST_element();
};

#endif