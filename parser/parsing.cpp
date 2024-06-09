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

    std::cerr << "wrong token " << current + 1
     << " expected data " << type << 
     " instead " << result.type << std::endl;
    
    current ++;
    return AST_element();
}

AST_element Parser::match_token_data(std::string data){
    token result = get_current();

    if(result.token_data == data){
        current ++;
        return AST_element(result);
    }

    std::cerr << "wrong token " << current + 1
     << " expected data " << data << 
     " instead " << result.token_data << std::endl;
    
    current ++;
    return AST_element();
}

AST_element Parser::parse_value(){
    AST_element result = AST_element();

    switch (get_current().type){
        case IDENTIFIER:
            result = match_token(IDENTIFIER);
            if(get_current().token_data == "("){
                match_token_data("(");
                if(get_current().token_data != ")"){
                    expression(result);
                }
                while(get_current().token_data == ","){
                    match_token_data(",");
                    expression(result);
                }
                match_token_data(")");
            }
            break;
        case NUMBER:
            result = match_token(NUMBER);
            break;
        default:
            std::cerr << "not value" << std::endl;
            break;
    }
    
    return result;
}

void Parser::expression(AST_element& context){
    AST_element result = parse_value();
    
    while(get_current().type == OPERATOR && get_current().token_data != ";"){
        AST_element op = match_token(OPERATOR);
        AST_element second = parse_value();

        op.add_depend(result);
        op.add_depend(second);

        result = op;    
    }

    context.add_depend(result);
}

AST_element Parser::parse(){
    AST_element main = AST_element(token{NULL_TOKEN, "module"});
    main.create_scope();
    main.get_scope()->add_pointer("print", {"print"});
    //std::cout << main.get_scope()->get_pointer("print").name;
    while (!is_parsed()){
        expression(main);
        match_token_data(";");
    }
    return main;
}

Parser::Parser(list_of_token tokens): tokens {tokens} {};