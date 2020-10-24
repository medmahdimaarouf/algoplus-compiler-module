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

std::string SyntaxicError::toString()
{
    return "(" + QString::number(this->ligneCode).toStdString() + "," + QString::number(this->columnLigne).toStdString() + ") : Syntaxic error -> " + QString::fromStdString( description).toStdString();
}

