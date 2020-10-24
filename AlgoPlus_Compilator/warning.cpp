#include "warning.h"

Warning::Warning()
{

}
Warning::Warning(int lignecode,int columnLigne):CompilationError(lignecode,columnLigne)
{

}

Warning::Warning(StdString description):CompilationError(description)
{

}

Warning::Warning(int lignecode, StdString description):CompilationError(lignecode,description)
{

}


