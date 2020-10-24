#ifndef WARNING_H
#define WARNING_H
#include "compilationerror.h"
class Warning : public CompilationError
{
public:
    Warning();
    Warning(int lignecode, int columnLigne);
    Warning(StdString description);
    Warning(int lignecode, StdString description);
};

#endif // WARNING_H
