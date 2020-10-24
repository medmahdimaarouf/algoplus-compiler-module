#ifndef COMPILATIONERROR_H
#define COMPILATIONERROR_H

#ifndef STDSTRING_H
#include<stdstring.h>
#endif

class CompilationError
{
public:
    CompilationError();
    CompilationError(int lignecode,int columLigne);
    CompilationError(StdString description);
    CompilationError(int lignecode, StdString description);
    CompilationError(int lignecode, int columLigne, StdString description);
    void setLigneCode(int lignecode);
    void setcolumnLigne(int columnLigne);
    unsigned int getLigneCode();
    unsigned int getcolumnLigne();
    StdString getDescription();
    void setDescription(StdString description);
    virtual StdString toString();
protected:
    int ligneCode;
    int columnLigne;
    StdString description;
};

#endif // COMPILATIONERROR_H
