#include "syntaxicerror.h"

SyntaxicError::SyntaxicError()
{
}

SyntaxicError::SyntaxicError(int lignecode):CompilationError(lignecode,0)
{

}

SyntaxicError::SyntaxicError(StdString description):CompilationError(description)
{

}

SyntaxicError::SyntaxicError(int lignecode, StdString description):CompilationError(lignecode,description)
{

}

SyntaxicError::SyntaxicError(int lignecode, int columnLigne, StdString description):CompilationError(lignecode,columnLigne,description)
{

}

StdString SyntaxicError::toString()
{
    return "(" + StdString::number(this->ligneCode) + "," + StdString::number(this->columnLigne) + ") : Syntaxic error -> " + ( description);
}

