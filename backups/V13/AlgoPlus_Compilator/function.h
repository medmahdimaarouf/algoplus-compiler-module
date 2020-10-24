#ifndef FUNCTION_H
#define FUNCTION_H
#include "procedure.h"

class Function   : public Procedure{
public:
    Function();
    explicit Function(Scope &parent);
    Function(std::string name, TypeOfContaint returnType);
    void setReturnType(TypeOfContaint returnType);
    TypeOfContaint getReturnType();
    void setReturnValue(NodeExpression * returnValue);

    NodeExpression * getReturnValue();
    bool hasRetournValue()const;
    std::string getWhat() const;
    void setWhat(const std::string &value);

    std::string toString();


private:
    TypeOfContaint returnType;
    std::string what = "FCT";
    NodeExpression *  returnValue = NULL;
};

#endif // FUNCTION_H
