#include "codegen.h"

void code_generation(AST_element ast, std::ostream &output){
    std::string preefect = "";
    std::string postefect = "";

    if(ast.primary_token.token_data == "module"){
        preefect = "(module";
        postefect = ")";
    }
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

    output << preefect << std::endl;
    for(std::list<AST_element>::iterator i = ast.get_iterator(); 
    i != ast.depend_tokens.end(); 
    i++){
        code_generation(*i, output);
    };
    output << postefect << std::endl;
}