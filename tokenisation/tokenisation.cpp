#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <iterator>

#include "token_type.h"

#include "tokenisation.h"

std::string token_to_string(token x){
    std::string result;
    result.append("{ ");
    result.append(std::to_string(x.type));
    result.append("; ");
    result.append(x.token_data);
    result.append(" }");
    return result;
}

list_of_token token_serialize(list_of_token token_list){
    std::ofstream myfile;
    myfile.open("tokens.txt");
    if(!myfile.is_open()){
        std::cout << "error in open file for token serializing" << std::endl;
    }

    std::vector<token>::iterator it;
    for( it = token_list->begin(); it != token_list->end(); it++){
        myfile << token_to_string(*it);
    }

    myfile.close();
    return token_list;
}

bool is_number(char x){
    return (48 <= x && x <= 57);
}

bool is_operator_char(char x){
    return (33 <= x && x <= 47) ||
           (58 <= x && x <= 63) ||
           (91 <= x && x <= 94) ||
           (123 <= x && x <= 126);
}

bool is_delimiter(char x){
    return x == ' ' || x == '\n';
}

token check_token(std::string raw_token){
    if (is_number(raw_token[0])){
        return token{NUMBER, raw_token};
    }
    if (is_operator_char(raw_token[0])){
        return token{OPERATOR, raw_token};
    }
    return token{};
}

list_of_token tokenisation(std::ifstream &code){
    list_of_token result = new std::vector<token>();

    std::string raw_token;
    while (!code.eof()){
        char f = code.get();
        if(is_delimiter(f)) {
            result->push_back(check_token(raw_token));
            raw_token = "";
        }
        else raw_token += f;
    };
    code.close();
    return result;
}

void token_list_delete(list_of_token x){
    delete x;
}