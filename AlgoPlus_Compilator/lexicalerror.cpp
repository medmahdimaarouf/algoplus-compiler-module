#include "lexicalerror.h"

LexicalError::LexicalError()
{

}

LexicalError::LexicalError(int lignecode,int columnLigne):CompilationError(lignecode,columnLigne)
{

}

LexicalError::LexicalError(StdString description):CompilationError(description)
{

}

LexicalError::LexicalError(int lignecode, StdString description):CompilationError(lignecode,description)
{

}

LexicalError::LexicalError(int lignecode,int columnLigne,StdString description):CompilationError(lignecode,columnLigne,description)
{

}

StdString LexicalError::toString()
{
    return "( Ligne  : " + StdString::number(ligneCode) + "  Colonne : " + StdString::number(columnLigne) + ")  Lexical error -> " + description;
}



