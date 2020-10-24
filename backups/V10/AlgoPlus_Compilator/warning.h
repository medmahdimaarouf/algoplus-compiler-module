#ifndef WARNING_H
#define WARNING_H
#include "compilationerror.h"
class Warning : public CompilationError
{
public:
    Warning();
    Warning(int lignecode, int columnLigne);
    Warning(std::string description);
    Warning(int lignecode, std::string description);
};

#endif // WARNING_H
