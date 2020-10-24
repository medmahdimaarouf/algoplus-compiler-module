#include "symanticerror.h"

SymanticError::SymanticError()
{

}

SymanticError::SymanticError(int lignecode,int columnLigne):CompilationError(lignecode,columnLigne)
{

}

SymanticError::SymanticError(StdString description):CompilationError(description)
{

}

SymanticError::SymanticError(int lignecode, StdString description):CompilationError(lignecode,description)
{

}

SymanticError::SymanticError(int lignecode,int columnLigne,StdString description):CompilationError(lignecode,columnLigne,description)
{

}

StdString SymanticError::toString()
{
    return "( Ligne  : " + StdString::number(ligneCode) + "  Colonne : " + StdString::number(columnLigne) + ")  Symantic Error error -> " + description;
}
