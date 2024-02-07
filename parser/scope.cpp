#include "scope.h"

void Scope::add_pointer(std::string key, pointer pointer){
    pointers.insert({key, pointer});
};


pointer Scope::get_pointer(std::string key){
    return pointers.at(key);
}