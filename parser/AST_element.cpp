#include <list>
#include <string>
#include <iterator>

#include "../tokenisation/tokenisation.h"

#include "AST_element.h"

AST_element::AST_element(token token): primary_token {token}{}

AST_element::AST_element(){
    primary_token = token{NULL_TOKEN, ""};
}

void AST_element::add_depend(AST_element depend){
    depend_tokens.push_back(depend);
}

std::list<AST_element>::iterator AST_element::get_iterator(){
    std::list<AST_element>::iterator it;
    it = depend_tokens.begin();
    return it;
}

std::string AST_element::to_string(){
    std::string result;
    result.append(token_to_string(primary_token));
    result.append("( ");
    for(std::list<AST_element>::iterator it = get_iterator(); it != depend_tokens.end(); it++){
        result.append(it->to_string());
        result.append(", ");
    }
    result.append(" )");
    return result;
}

void AST_element::pop_depend(){
    depend_tokens.pop_back();
}

AST_element AST_element::get_last_depend(){
    return depend_tokens.back();
}