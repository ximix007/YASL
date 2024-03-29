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

void AST_element::output(std::ostream &output){
    output << token_to_string(primary_token);
    
    if(depend_tokens.empty()) return;

    output << "( ";
    for(std::list<AST_element>::iterator it = get_iterator(); it != depend_tokens.end(); it++){
        it->output(output);
        output << ", ";
    }
    output << " )";
}

void AST_element::pop_depend(){
    depend_tokens.pop_back();
}

AST_element AST_element::get_last_depend(){
    return depend_tokens.back();
}

void AST_element::create_scope(){
    scope = new Scope();
}

Scope* AST_element::get_scope(){
    return scope;
}

AST_element::~AST_element(){
    if(scope != nullptr) delete scope;
}