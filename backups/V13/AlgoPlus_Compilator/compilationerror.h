#ifndef COMPILATIONERROR_H
#define COMPILATIONERROR_H
#include<iostream>
#include<stringOperations.h>

class CompilationError
{
public:
    CompilationError();
    CompilationError(int lignecode,int columLigne);
    CompilationError(std::string description);
    CompilationError(int lignecode, std::string description);
    CompilationError(int lignecode, int columLigne, std::string description);
    void setLigneCode(int lignecode);
    void setcolumnLigne(int columnLigne);
    unsigned int getLigneCode();
    unsigned int getcolumnLigne();
    std::string getDescription();
    void setDescription(std::string description);
    virtual std::string toString();
protected:
    int ligneCode;
    int columnLigne;
    std::string description;
};

#endif // COMPILATIONERROR_H
