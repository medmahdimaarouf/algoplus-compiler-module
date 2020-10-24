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

QString LexicalError::toString()
{
    return "( Ligne  : " + QString::number(ligneCode) + "  Colonne : " + QString::number(columnLigne) + ")  Lexical error -> " + QString::fromStdString(description );
}



