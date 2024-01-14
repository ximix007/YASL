#include <iostream>
#include <fstream>
#include "tokenisation/tokenisation.h"

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
        token_serialize(token_list);
        token_list_delete(token_list);
    }
    else{
        std::cout << "File error: " << argv[1] << " doesnt exist." << std::endl;
    }
    return 0;
}