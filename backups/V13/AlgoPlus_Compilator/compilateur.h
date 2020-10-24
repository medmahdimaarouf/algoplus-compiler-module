#ifndef COMPILATEUR_H
#define COMPILATEUR_H

#include "syntaxicanalyser.h"
#include "mainscope.h"
#include "warning.h"

#ifndef ListErrors
typedef std::list<CompilationError> ListErrors;
#endif

#ifndef ListWarnings
typedef std::list<Warning> ListWarnings;
#endif

class Compilateur
{
public:
    explicit Compilateur();
    static MainScope * ParseTree;
    void Compiler();
    void Clear();
private:
    ListErrors listErrors;
    ListWarnings listWarning;
};

#endif // COMPILATEUR_H
