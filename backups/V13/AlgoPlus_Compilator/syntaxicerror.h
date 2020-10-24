#ifndef SYNTAXICERROR_H
#define SYNTAXICERROR_H
#include<QObject>
#include "compilationerror.h"
class SyntaxicError : public CompilationError
{
public:
    SyntaxicError();
    SyntaxicError(int lignecode);
    SyntaxicError(std::string description);
    SyntaxicError(int lignecode, std::string description);
    SyntaxicError(int lignecode, int columnLigne, std::string description);
    std::string toString();
private :

};

#endif // SYNTAXICERROR_H
