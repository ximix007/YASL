#ifndef CODEGEN_H
#define CODEGEN_H

#include <iostream>
#include <string>

#include "../parser/AST_element.h"

void code_generation(AST_element ast,
                std::ostream &output,
                AST_element parent = AST_element(),
                unsigned position = 0);

#endif