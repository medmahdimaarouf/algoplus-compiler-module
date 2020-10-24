#include "function.h"

Function::Function():Procedure()
{

}

Function::Function(Scope &parent):Procedure(parent)
{

}

Function::Function(QString name, TypeOfContaint returnType):Procedure(name)
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

std::string Function::toString()
{
    std::string desc = "\n FUNCTION " + this->getName().toStdString() + " (",desc2;
    for(int i = 0; i < this->getArgs().size();i++)
    {
        Argment arg = this->getArgs().at(i);
        desc2 += "," + arg.toString();
    }
    if(!desc2.empty())
        desc2[0] = ' ';
    desc += desc2;
    std::string tt = "";
    for(int i = 0; i < this->returnType.getMemoryRange();i++)
        tt += "@";
    desc += ") : " + tt +this->returnType.getName().toStdString();
    desc += "\n" + this->Scope::toString();
    return desc;
}
