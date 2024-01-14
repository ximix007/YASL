#include <list>
#include <fstream>

struct token;

typedef std::list<token>* list_of_token;

list_of_token tokenisation(std::ifstream &code);

list_of_token token_serialize(list_of_token token_list);

void token_list_delete(list_of_token x);
