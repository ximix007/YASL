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

token Parser::get_next(){
    if(current+1 >= tokens->size()) return {NULL_TOKEN, ""};
    return tokens->at(current+1);
}

AST_element Parser::match_token(token_type type){
    token result = get_current();

    if(result.type == type){
        current ++;
        return AST_element(result);
    }

    std::cerr << "wrong token " << current + 1
     << " expected type " << type << 
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
                    simple_expression(result);
                }
                while(get_current().token_data == ","){
                    match_token_data(",");
                    simple_expression(result);
                }
                match_token_data(")");
            }
            break;
        case NUMBER:
            result = match_token(NUMBER);
            break;
        default:
            std::cerr << "not value " << std::endl;
            break;
    }
    
    return result;
}

void Parser::simple_expression(AST_element& context){
    AST_element result = parse_value();
    
    while(get_current().type == OPERATOR){
        AST_element op = match_token(OPERATOR);
        AST_element second = parse_value();

        op.add_depend(result);
        op.add_depend(second);

        result = op;
    }

    context.add_depend(result);
}

void Parser::expression(AST_element& context){
    if((get_current().type == IDENTIFIER &&
    get_next().type != IDENTIFIER) ||
    get_current().type == NUMBER){
       simple_expression(context);
    }
    if(get_current().token_data == "func"){
        function_declaration(context);
    }
    if(get_next().token_data == "=" ||
    (get_current().type == IDENTIFIER &&
    get_next().type == IDENTIFIER)){
        assignment(context);
    }
}

void Parser::assignment(AST_element& context){
    AST_element variable = match_token(IDENTIFIER);
    if(get_current().type == IDENTIFIER){
        AST_element temp = match_token(IDENTIFIER);
        temp.add_depend(variable);
        variable = temp;
    }

    if(get_current().token_data == "="){
        AST_element assignment = AST_element(match_token_data("="));
        assignment.add_depend(variable);
        simple_expression(assignment);
        variable = assignment;
    }
    context.add_depend(variable);
}

void Parser::function_declaration(AST_element& context){
    AST_element result = AST_element(match_token_data("func"));
    AST_element type = AST_element(match_token(IDENTIFIER));
    result.add_depend(type);
    AST_element name = AST_element(match_token(IDENTIFIER));
    result.add_depend(name);
    
    AST_element arguments = AST_element(match_token_data("("));
    if(get_current().token_data != ")"){
        AST_element type = match_token(IDENTIFIER);
        AST_element variable = match_token(IDENTIFIER);
        variable.add_depend(type);
        arguments.add_depend(variable);
    }
    while(get_current().token_data == ","){
        match_token_data(",");
        AST_element type = match_token(IDENTIFIER);
        AST_element variable = match_token(IDENTIFIER);
        variable.add_depend(type);
        arguments.add_depend(variable);
    }
    result.add_depend(arguments);
    match_token_data(")");

    AST_element body = AST_element(match_token_data("{"));
    while(get_current().token_data != "}"){
        if(get_current().token_data == "return"){
            AST_element return_ = AST_element(match_token_data("return"));
            simple_expression(return_);
            match_token_data(";");
            body.add_depend(return_);
        } else {
            simple_expression(body);
            match_token_data(";");
        }
    }
    match_token_data("}");
    result.add_depend(body);

    context.add_depend(result);
}

AST_element Parser::parse(){
    AST_element main = AST_element(token{NULL_TOKEN, "module"});
    main.create_scope();
    main.get_scope()->add_pointer("print", {"print"});
    while (!is_parsed()){
        expression(main);
        match_token_data(";");
    }
    return main;
}

Parser::Parser(list_of_token tokens): tokens {tokens} {};