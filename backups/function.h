#ifndef FUNCTION_H
#define FUNCTION_H
#include "procedure.h"

class Function   : public Procedure{
public:
    Function();
    explicit Function(Scope &parent);
    Function(QString name,Type returnType);
    void setReturnType(Type returnType);
    Type getReturnType();
private:
    Type returnType;
    QString what = "FCT";

};

#endif // FUNCTION_H
