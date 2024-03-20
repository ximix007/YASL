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

token Parser::get_current(){
    return tokens->at(current);
}

AST_element Parser::match_token(token_type type){
    token result = get_current();

    if(result.type == type){
        current ++;
        return AST_element(result);
    }

    current ++;
    std::cerr << "wrong token" << std::endl;
    return AST_element();
}

AST_element Parser::parse_value(){
    AST_element result = AST_element();
    token_type type = NULL_TOKEN;

    switch (get_current().type){
        case IDENTIFIER:
            type = IDENTIFIER;
            break;
        case NUMBER:
            type = NUMBER;
            break;
        default:
            std::cerr << "not value" << std::endl;
            break;
    }
    result = match_token(type);

    return result;
}

void Parser::expression(AST_element& context){
    AST_element result = parse_value();
    
    for(; get_current().token_data != ";"; ){
        AST_element op = match_token(OPERATOR);
        AST_element second = parse_value();

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
    //std::cout << main.get_scope()->get_pointer("print").name;
    while (!is_parsed()){
        expression(main);
    }
    return main;
}

Parser::Parser(list_of_token tokens): tokens {tokens} {};