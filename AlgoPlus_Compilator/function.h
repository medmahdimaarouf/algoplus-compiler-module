#ifndef FUNCTION_H
#define FUNCTION_H
#include "procedure.h"

class Function   : public Procedure{
public:
    Function();
    explicit Function(Scope &parent);
    Function(StdString name, TypeOfContaint returnType);
    void setReturnType(TypeOfContaint returnType);
    TypeOfContaint getReturnType();
    void setReturnValue(NodeExpression * returnValue);

    NodeExpression * getReturnValue();
    bool hasRetournValue()const;
    StdString getWhat() const;
    void setWhat(const StdString &value);

    StdString toString();


private:
    TypeOfContaint returnType;
    StdString what = StdString("FCT");
    NodeExpression *  returnValue = NULL;
};

#endif // FUNCTION_H
