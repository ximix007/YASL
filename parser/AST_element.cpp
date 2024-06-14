#include "AST_element.h"

AST_element::AST_element(token p_token): p_token {p_token}{}

AST_element::AST_element(){
    p_token = token{NULL_TOKEN, ""};
}

void AST_element::add_depend(AST_element depend){
    depend_tokens.push_back(depend);
}

std::vector<AST_element>::iterator AST_element::get_iterator(){
    std::vector<AST_element>::iterator it;
    it = depend_tokens.begin();
    return it;
}

void AST_element::output(std::ostream &output){
    output << token_to_string(p_token);
    
    if(depend_tokens.empty()) return;

    output << "( ";
    for(std::vector<AST_element>::iterator it = get_iterator(); it != depend_tokens.end(); it++){
        it->output(output);
        output << ", ";
    }
    output << " )";
}

void AST_element::pop_depend(){
    depend_tokens.pop_back();
}

void AST_element::create_scope(){
    scope = Scope();
}

Scope* AST_element::get_scope(){
    return &scope;
}