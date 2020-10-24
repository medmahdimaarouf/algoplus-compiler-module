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

QString SymanticError::toString()
{
    return "( Ligne  : " + QString::number(ligneCode) + "  Colonne : " + QString::number(columnLigne) + ")  Symantic Error error -> " + QString::fromStdString( description );
}
