#include "procedure.h"

Procedure::Procedure()
{
    args = new MapArgs();
}

Procedure::Procedure(Scope &parent):Scope(parent){
    args = new MapArgs();
}

Procedure::Procedure(std::string name):Scope(name){}

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
        this->args->insert(std::make_pair<std::string,Argment>(arg.getName(),arg));
    }
}

bool Procedure::hasArg(std::string argname)
{
    return this->args->count(argname);
}

Argment Procedure::getArg(std::string name)
{
    return args->at(name);
}

void Procedure::CheckExistID(std::string id)
{
    if(this->hasArg(toUpper(id)))
        throw "'" + id + "' deja declare comme un argumant";
    else
        this->Scope::CheckExistID(id);

}

std::string Procedure::toString()
{
    std::string desc = "\n PROCEDURE " + this->getName() + " (",desc2;
    ListArgs listArgs = getArgs();
    for(ListArgs::iterator i = listArgs.begin(); i != listArgs.end();i++)
    {
        Argment arg = *i;
        desc2 += "," + arg.toString();
    }
    if(!desc2.empty())
        desc2[0] = ' ';
    desc += desc2;
    desc += ")";
    desc += "\n" + this->Scope::toString();
    return desc;

}
