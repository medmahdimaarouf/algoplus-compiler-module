#include "function.h"

Function::Function():Procedure()
{

}

Function::Function(Scope &parent):Procedure(parent)
{

}

Function::Function(QString name, Type returnType):Procedure(name)
{
    this->returnType = returnType;
}

void Function::setReturnType(Type returnType)
{
    this->returnType = returnType;
}

Type Function::getReturnType()
{
    return returnType;
}
