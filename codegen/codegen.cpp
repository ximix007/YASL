#include "codegen.h"

void code_generation(AST_element ast, std::ostream &output, AST_element parent, unsigned position){
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
    if(ast.primary_token.token_data == "func"){
        preefect = "(func";
        postefect = ")";
    }
    if(ast.primary_token.type == IDENTIFIER){
        if(parent.primary_token.token_data == "func"){
            if(position == 0){
                if(ast.primary_token.token_data == "int"){
                    preefect = "(result i32)";
                }
            }
            if(position == 1){
                preefect.append("(export \"");
                preefect.append(ast.primary_token.token_data);
                preefect.append("\")");
            }
        }
    }

    output << preefect << std::endl;
    unsigned j = 0;
    for(std::list<AST_element>::iterator i = ast.get_iterator(); 
    i != ast.depend_tokens.end(); 
    i++){
        code_generation(*i, output, ast, j);
        j++;
    };
    output << postefect;
}