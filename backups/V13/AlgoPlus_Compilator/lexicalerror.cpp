#include "lexicalerror.h"

LexicalError::LexicalError()
{

}

LexicalError::LexicalError(int lignecode,int columnLigne):CompilationError(lignecode,columnLigne)
{

}

LexicalError::LexicalError(std::string description):CompilationError(description)
{

}

LexicalError::LexicalError(int lignecode, std::string description):CompilationError(lignecode,description)
{

}

LexicalError::LexicalError(int lignecode,int columnLigne,std::string description):CompilationError(lignecode,columnLigne,description)
{

}

std::string LexicalError::toString()
{
    return "( Ligne  : " + QString::number(ligneCode).toStdString() + "  Colonne : " + QString::number(columnLigne).toStdString() + ")  Lexical error -> " + QString::fromStdString(description ).toStdString();
}



