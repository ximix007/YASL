#include <iterator>

#include "../tokenisation/tokenisation.h"
#include "../tokenisation/token_type.h"
#include "AST_element.h"

#include "parsing.h"

std::string parsing(list_of_token tokens){
    AST_element main = AST_element(token{NULL_TOKEN, "main"});
    
    std::list<token>::iterator it;
    for(it = tokens->begin(); it != tokens->end(); it++){
        main.add_depend(AST_element(*it));
    }

    return main.to_string();
}