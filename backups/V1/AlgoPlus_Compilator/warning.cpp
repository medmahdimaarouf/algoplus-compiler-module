#include "warning.h"

Warning::Warning()
{
}
Warning::Warning(int lignecode,int columnLigne):CompilationError(lignecode,columnLigne)
{

}

Warning::Warning(std::string description):CompilationError(description)
{

}

Warning::Warning(int lignecode, std::string description):CompilationError(lignecode,description)
{

}


