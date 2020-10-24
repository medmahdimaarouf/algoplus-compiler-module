#include "procedure.h"

Procedure::Procedure()
{
    args = new QMap<QString, Argment>();
}

Procedure::Procedure(Scope &parent):Scope(parent){
    args = new QMap<QString, Argment>();
}

Procedure::Procedure(QString name):Scope(name){}

void Procedure::setArgs(QMap<QString, Argment> *args)
{
    this->args = args;
}

QMap<QString, Argment> *Procedure::getArgs()
{
    return this->args;
}

void Procedure::addArg(Argment arg)
{
    if(this->hasArg(arg.getName()))
        throw SyntaxicError("Argument existe deja");
    else
        this->args->insert(arg.getName(),arg);
}

bool Procedure::hasArg(QString argname)
{
    return this->args->contains(argname);
}

Argment Procedure::getArg(QString name)
{
    return args->value(name,Argment());
}
