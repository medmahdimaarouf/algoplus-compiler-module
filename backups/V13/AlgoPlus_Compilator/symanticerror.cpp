#include "symanticerror.h"

SymanticError::SymanticError()
{

}

SymanticError::SymanticError(int lignecode,int columnLigne):CompilationError(lignecode,columnLigne)
{

}

SymanticError::SymanticError(std::string description):CompilationError(description)
{

}

SymanticError::SymanticError(int lignecode, std::string description):CompilationError(lignecode,description)
{

}

SymanticError::SymanticError(int lignecode,int columnLigne,std::string description):CompilationError(lignecode,columnLigne,description)
{

}

std::string SymanticError::toString()
{
    return "( Ligne  : " + Number(ligneCode) + "  Colonne : " + Number(columnLigne) + ")  Symantic Error error -> " + description;
}
