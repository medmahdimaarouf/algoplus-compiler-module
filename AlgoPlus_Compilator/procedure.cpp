#include "procedure.h"

Procedure::Procedure()
{
    args = new MapArgs();
}

Procedure::Procedure(Scope &parent):Scope(parent){
    args = new MapArgs();
}

Procedure::Procedure(StdString name):Scope(name){}

void Procedure::setArgs(MapArgs *args)
{
    this->args = args;
}

ListArgs Procedure::getArgs()
{
    ListArgs listArgs;
    for(MapArgs::iterator iterator = args->begin(); iterator != args->end();iterator++){
        listArgs.push_back(iterator->second);
    }
    return listArgs;
}

void Procedure::addArg(Argment arg)
{
    this->CheckExistID(arg.getName());
    if(this->hasArg(arg.getName()))
        throw SyntaxicError("Argument existe deja");
    else{
        this->args->insert(std::make_pair<StdString,Argment>(arg.getName(),arg));
    }
}

bool Procedure::hasArg(StdString argname)
{
    return this->args->count(argname);
}

Argment Procedure::getArg(StdString name)
{
    return args->at(name);
}

void Procedure::CheckExistID(StdString id)
{
    if(this->hasArg(id.toUpper()))
        throw "'" + id + "' deja declare comme un argumant";
    else
        this->Scope::CheckExistID(id);

}

StdString Procedure::toString()
{
    StdString desc = "\n PROCEDURE " + this->getName() + " (",desc2;
    ListArgs listArgs = getArgs();
    for(ListArgs::iterator i = listArgs.begin(); i != listArgs.end();i++)
    {
        Argment arg = *i;
        desc2 += "," + arg.toString();
    }
    if(!desc2.isEmpty())
        desc2[0] = ' ';
    desc += desc2;
    desc += ")";
    desc += "\n" + this->Scope::toString();
    return desc;

}
