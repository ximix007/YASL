#include "tokenisation.h"

std::string token_to_string(token x){
    std::string result;
    result.append("{ ");
    result.append(std::to_string(x.type));
    result.append("; ");
    result.append("\"");
    result.append(x.token_data);
    result.append("\"");
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
        myfile << token_to_string(*it) << std::endl;
    }

    myfile.close();
    return token_list;
}

bool is_number(char x){
    return (48 <= x && x <= 57);
}

bool is_operator_char(char x){
    return (33 <= x && x <= 39) ||
           (42 <= x && x <= 43) ||
           (45 <= x && x <= 47) ||
           (60 <= x && x <= 63) ||
           (91 <= x && x <= 94) ||
           x == '|' || x == ':' ||
           x == '~';
}

bool is_identifier_char(char x){
    return  (65 <= x && x <= 90) ||
            (97 <= x && x <= 122) ||
            (x == '_');
}

bool is_delimiter(char x){
    return x == ' ' || x == '\n';
}

bool is_punctuator(char x){
    return x == '(' || x == ')' ||
    x == '{' || x == '}' || x == ';';
}

token check_token(std::string raw_token){
    if (is_number(raw_token[0])){
        return token{NUMBER, raw_token};
    }
    if (is_operator_char(raw_token[0])){
        return token{OPERATOR, raw_token};
    }
    if (is_identifier_char(raw_token[0])){
        for(unsigned int i = 0; i < KEYWORD_COUNT ; i++)
            if(raw_token == keywords[i]) return token{KEYWORD, raw_token};
        return token{IDENTIFIER, raw_token};
    }
    if (is_punctuator(raw_token[0])){
        return token{PUNCTUATOR, raw_token};
    }
    if (raw_token[0] == ','){
        return token{COMA, raw_token};
    }
    return token{NULL_TOKEN, raw_token};
}

list_of_token tokenisation(std::ifstream &code){
    list_of_token result = new std::vector<token>();

    while (!code.eof()){
        std::string current_line;
        std::getline(code, current_line);

        for(unsigned i = 0; i < current_line.size(); i++){
            if(is_delimiter(current_line[i])) continue;
            unsigned temp = i;
            if(is_number(current_line[i])){
                while(is_number(current_line[i+1])){
                    i++;
                }
            }
            if(is_operator_char(current_line[i])){
                while(is_operator_char(current_line[i+1])){
                    i++;
                }
            }
            if(is_identifier_char(current_line[i])){
                while(is_identifier_char(current_line[i+1])){
                    i++;
                }
            }

            if(current_line.substr(temp, i-temp + 1) == "//") break;
            result->push_back(check_token(current_line.substr(temp, i-temp + 1)));
        }
    };
    code.close();
    return result;
}

void token_list_delete(list_of_token x){
    delete x;
}