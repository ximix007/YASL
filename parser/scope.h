#ifndef SCOPE_H
#define SCOPE_H

#include <string>
#include <unordered_map>

struct pointer{
    std::string name;
};

class Scope{
    std::unordered_map<std::string, pointer> pointers = std::unordered_map<std::string, pointer>();

public:
    void add_pointer(std::string key, pointer pointer);

    pointer get_pointer(std::string key);
};

#endif