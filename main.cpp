#include <iostream>
#include <fstream>
#include "parser/AST_element.h"
#include "tokenisation/tokenisation.h"
#include "parser/parsing.h"
#include "codegen/codegen.h"

int main(int argc, char* argv[])
{
    if(argc < 2){
        std::cout << "Missing file name." << std::endl;
        return -1;
    }
    std::ifstream source_code;
    source_code.open(argv[1]);
    if (source_code.is_open()){
        list_of_token token_list = tokenisation(source_code);
        std::cout << "Tokenized" << std::endl;
        token_serialize(token_list);
        Parser parser = Parser(token_list);

        std::ofstream parsedump;
        parsedump.open("AST.txt");
        AST_element ast = parser.parse();
        ast.output(parsedump);
        parsedump.close();

        std::ofstream wat;
        wat.open("code.wat");
        code_generation(ast, wat);
        wat.close();

        token_list_delete(token_list);

        std::cout << "Build succeseful" << std::endl;
    }
    else{
        std::cout << "File error: " << argv[1] << " doesnt exist." << std::endl;
    }
    return 0;
}