#ifndef CODEGEN_H
#define CODEGEN_H

#include "../parser/AST_element.h"
#include "string"

void code_generation(AST_element ast, std::ostream &output);

#endif