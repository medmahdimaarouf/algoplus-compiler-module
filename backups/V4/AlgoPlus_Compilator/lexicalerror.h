#ifndef LEXICALERROR_H
#define LEXICALERROR_H

#include <QObject>
#include "compilationerror.h"
class LexicalError : public CompilationError
{

public:
     LexicalError();
     LexicalError(int lignecode,int columnLigne);
     LexicalError(std::string description);
     LexicalError(int lignecode, std::string description);
     LexicalError(int lignecode, int columnLigne, std::string description);
     QString toString();
};

#endif // LEXICALERROR_H
