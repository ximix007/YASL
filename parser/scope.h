#ifndef SCOPE_H
#define SCOPE_H

#include <iostream>
#include <string>
#include <unordered_map>

struct pointer{
    std::string type;
    bool local;
    std::string address;
};

class Scope{
    std::unordered_map<std::string, pointer> pointers = std::unordered_map<std::string, pointer>();
    Scope* outer = nullptr;

public:
    void add_pointer(std::string key, pointer pointer);

    void set_outer(Scope* new_outer);

    void print_scope();

    pointer get_pointer(std::string key);
};

#endif