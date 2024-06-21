#include "scope.h"

void Scope::add_pointer(std::string key, pointer pointer){
    pointers.insert({key, pointer});
};

void Scope::set_outer(Scope* new_outer){
    outer = new_outer;
};

pointer Scope::get_pointer(std::string key){
    try{
        return pointers.at(key);
    }
    catch(std::out_of_range e){
        if(outer != nullptr){
            return outer->get_pointer(key);
        }
    }
    return {};
}

void Scope::print_scope(){
    if(outer != nullptr){
        outer->print_scope();
    }

    for(std::unordered_map<std::string, pointer>::iterator i = pointers.begin(); 
    i != pointers.end(); 
    i++){
        std::cout << i->first << std::endl;
    };
}