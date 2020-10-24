#ifndef FUNCTION_H
#define FUNCTION_H
#include "procedure.h"

class Function   : public Procedure{
public:
    Function();
    explicit Function(Scope &parent);
    Function(QString name, TypeOfContaint returnType);
    void setReturnType(TypeOfContaint returnType);
    TypeOfContaint getReturnType();
    std::string toString();
private:
    TypeOfContaint returnType;
    QString what = "FCT";

};

#endif // FUNCTION_H
