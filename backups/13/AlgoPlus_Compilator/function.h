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
    void setReturnValue(NodeExpression * returnValue);

    NodeExpression * getReturnValue();
    bool hasRetournValue()const;
    QString getWhat() const;
    void setWhat(const QString &value);

    std::string toString();


private:
    TypeOfContaint returnType;
    QString what = "FCT";
    NodeExpression *  returnValue = NULL;
};

#endif // FUNCTION_H
