#ifndef SYMANTICERROR_H
#define SYMANTICERROR_H

#include<compilationerror.h>

class SymanticError : public CompilationError
{
public:
    SymanticError();
    SymanticError(int lignecode,int columnLigne);
    SymanticError(std::string description);
    SymanticError(int lignecode, std::string description);
    SymanticError(int lignecode, int columnLigne, std::string description);
    std::string toString();

};

#endif // SYMANTICERROR_H
