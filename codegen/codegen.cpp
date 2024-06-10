#include "codegen.h"

void expressions_generation(AST_element ast, std::ostream &output, Scope* context){
    std::string preefect = "";
    std::string postefect = "";

    if(ast.primary_token.type == OPERATOR){
        if(ast.primary_token.token_data == "+"){
            postefect = "i32.add";
        }
        if(ast.primary_token.token_data == "-"){
            postefect = "i32.sub";
        }
        if(ast.primary_token.token_data == "*"){
            postefect = "i32.mul";
        }
    }
    if(ast.primary_token.type == NUMBER){
        preefect = "i32.const " + ast.primary_token.token_data;
    }
    if(ast.primary_token.type == IDENTIFIER){
        if(ast.depend_tokens.empty()){
            preefect = "local.get ";
            postefect = context->get_pointer(ast.primary_token.token_data).address;
        }
    };

    output << preefect;
    for(std::vector<AST_element>::iterator i = ast.get_iterator(); 
    i != ast.depend_tokens.end(); 
    i++){
        expressions_generation(*i, output, context);
    };
    output << postefect << std::endl;
    output.flush();
};

void function_processing(AST_element ast, std::ostream &output){
    ast.create_scope();
    output << "(func";

    output << "(export \""
    << ast.depend_tokens[1].primary_token.token_data
    << "\")" << std::endl;

    std::vector<AST_element> arguments = ast.depend_tokens[2].depend_tokens;
    if(arguments.size()){
        output << "(param ";
        for(unsigned i = 0; i < arguments.size(); i++){
            if(arguments[i].depend_tokens[0].primary_token.token_data == "int"){
                output << "i32 ";
                ast.get_scope()->add_pointer(arguments[i].primary_token.token_data, {"int", true, std::to_string(i)});
            }
        };
        output << ")"  << std::endl;
    }

    if(ast.depend_tokens[0].primary_token.token_data != "void"){
        std::string type = "";
        if(ast.depend_tokens[0].primary_token.token_data == "int")
            type = "i32";
        output << "(result " << type << ")"  << std::endl;
    }

    for(unsigned i = 0; i < ast.depend_tokens[3].depend_tokens.size(); i++){
        expressions_generation(ast.depend_tokens[3].depend_tokens[i], output, ast.get_scope());
    };

    output << ")" << std::endl;
}

void code_generation(AST_element ast, std::ostream &output, AST_element parent, unsigned position){
    output << "(module" << std::endl;
    
    for(unsigned i = 0; i < ast.depend_tokens.size(); i++){
        if(ast.depend_tokens[i].primary_token.token_data == "func"){
            function_processing(ast.depend_tokens[i], output);
        }
    };
    
    output << ")" << std::endl;
}