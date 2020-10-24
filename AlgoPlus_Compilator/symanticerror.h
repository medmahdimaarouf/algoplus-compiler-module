#ifndef SYMANTICERROR_H
#define SYMANTICERROR_H

#include<compilationerror.h>

class SymanticError : public CompilationError
{
public:
    SymanticError();
    SymanticError(int lignecode,int columnLigne);
    SymanticError(StdString description);
    SymanticError(int lignecode, StdString description);
    SymanticError(int lignecode, int columnLigne, StdString description);
    StdString toString();

};

#endif // SYMANTICERROR_H
