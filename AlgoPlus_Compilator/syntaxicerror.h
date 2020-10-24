#ifndef SYNTAXICERROR_H
#define SYNTAXICERROR_H
#include "compilationerror.h"
class SyntaxicError : public CompilationError
{
public:
    SyntaxicError();
    SyntaxicError(int lignecode);
    SyntaxicError(StdString description);
    SyntaxicError(int lignecode, StdString description);
    SyntaxicError(int lignecode, int columnLigne, StdString description);
    StdString toString();
private :

};

#endif // SYNTAXICERROR_H
