#ifndef LEXICALERROR_H
#define LEXICALERROR_H

#include "compilationerror.h"
class LexicalError : public CompilationError
{

public:
     LexicalError();
     LexicalError(int lignecode,int columnLigne);
     LexicalError(StdString description);
     LexicalError(int lignecode, StdString description);
     LexicalError(int lignecode, int columnLigne, StdString description);
     StdString toString();
};

#endif // LEXICALERROR_H
