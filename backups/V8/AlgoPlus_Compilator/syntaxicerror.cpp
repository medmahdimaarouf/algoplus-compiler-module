#include "syntaxicerror.h"

SyntaxicError::SyntaxicError()
{
}

SyntaxicError::SyntaxicError(int lignecode):CompilationError(lignecode,0)
{

}

SyntaxicError::SyntaxicError(std::string description):CompilationError(description)
{

}

SyntaxicError::SyntaxicError(int lignecode, std::string description):CompilationError(lignecode,description)
{

}

SyntaxicError::SyntaxicError(int lignecode, int columnLigne, std::string description):CompilationError(lignecode,columnLigne,description)
{

}

QString SyntaxicError::toString()
{
    return "(" + QString::number(this->ligneCode) + "," + QString::number(this->columnLigne) + ") : Syntaxic error -> " + QString::fromStdString( description);
}

