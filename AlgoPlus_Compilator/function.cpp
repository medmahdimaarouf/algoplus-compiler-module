#include "function.h"

Function::Function():Procedure()
{

}

Function::Function(Scope &parent):Procedure(parent)
{

}

Function::Function(StdString name, TypeOfContaint returnType):Procedure(name)
{
    this->returnType = returnType;
}

void Function::setReturnType(TypeOfContaint returnType)
{
    this->returnType = returnType;
}

TypeOfContaint Function::getReturnType()
{
    return returnType;
}

StdString Function::toString()
{

    StdString desc = "\n FUNCTION " + this->getName() + " (",desc2 = StdString("");
    for(ListArgs::iterator iterator = this->getArgs().begin(); iterator != this->getArgs().end();iterator.operator ++())
    {
        Argment arg = *iterator;
        desc2 += "," + arg.toString();
    }
    if(!desc2.isEmpty())
        desc2[0] = ' ';
    desc += desc2;
    StdString tt = StdString("");
    for(int i = 0; i < this->returnType.getMemoryRange();i++)
        tt += "@";
    desc += ") : " + tt +this->returnType.getName();
    desc += "\n" + this->Scope::toString();
    desc.insert(desc.size() - 8,"\n [ Retourner " + returnValue->toString() + " ] \n");
    return desc;
}

void Function::setReturnValue(NodeExpression *returnValue){
    if(hasRetournValue())
        throw StdString("Erreur fatal  : Duplication de retour de fonction interdit");
    else
        this->returnValue = returnValue;
}

NodeExpression *Function::getReturnValue(){return returnValue;}

bool Function::hasRetournValue() const {
    return returnValue != NULL;
}

StdString Function::getWhat() const
{
    return what;
}

void Function::setWhat(const StdString &value)
{
    what = value;
}

