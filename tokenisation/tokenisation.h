#ifndef TOKENISATION_H
#define TOKENISATION_H

#include <fstream>
#include <vector>
#include "token_type.h"

struct token{
    token_type type;
    std::string token_data;
};

typedef std::vector<token>* list_of_token;

list_of_token tokenisation(std::ifstream &code);

list_of_token token_serialize(list_of_token token_list);

void token_list_delete(list_of_token x);

std::string token_to_string(token x);

#endif
