#include <iterator>
#include <iostream>
#include <exception>

#include "parsing.h"

bool Parser::is_parsed(){
    if(current < tokens->size()){
        return false;
    }
    return true;
}

AST_element Parser::match_token(token_type type){
    token result = tokens->at(current);

    if(result.type == type){
        current ++;
        return AST_element(result);
    }

    current ++;
    std::cerr << "wrong token" << std::endl;
    return AST_element();
}

void Parser::expression(AST_element& context){
    AST_element result = match_token(NUMBER);
    
    for(; (*tokens)[current].token_data != ";"; ){
        AST_element op = match_token(OPERATOR);
        AST_element second = match_token(NUMBER);

        op.add_depend(result);
        op.add_depend(second);

        result = op;    
    }

    current++;
    context.add_depend(result);
}

AST_element Parser::parse(){
    AST_element main = AST_element(token{NULL_TOKEN, "main"});
    main.create_scope();
    main.get_scope()->add_pointer("print", {"print"});
    std::cout << main.get_scope()->get_pointer("print").name;
    while (!is_parsed()){
        expression(main);
    }
    return main;
}

Parser::Parser(list_of_token tokens): tokens {tokens} {};