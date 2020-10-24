#ifndef COMPILATIONERROR_H
#define COMPILATIONERROR_H

#include<QObject>

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
    int getLigneCode();
    std::string getDescription();
    int getcolumnLigne();
    void setDescription(std::string description);
    virtual QString toString();
protected:
    int ligneCode;
    int columnLigne;
    std::string description;
};

#endif // COMPILATIONERROR_H
