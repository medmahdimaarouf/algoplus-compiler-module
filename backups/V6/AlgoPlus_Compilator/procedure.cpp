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

QList<Argment> Procedure::getArgs()
{
    return this->args->values();
}

void Procedure::addArg(Argment arg)
{
    this->CheckExistID(arg.getName().toStdString());
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

void Procedure::CheckExistID(std::string id)
{
    if(this->hasArg(QString::fromStdString(id).toUpper()))
        throw "'" + id + "' deja declare comme un argumant";
    else
        this->Scope::CheckExistID(id);

}

std::string Procedure::toString()
{
    std::string desc = "\n PROCEDURE " + this->getName().toStdString() + " (",desc2;
    for(int i = 0; i < this->getArgs().size();i++)
    {
        Argment arg = this->getArgs().at(i);
        desc2 += "," + arg.toString();
    }
    if(!desc2.empty())
        desc2[0] = ' ';
    desc += desc2;
    desc += ")";
    desc += "\n" + this->Scope::toString();
    return desc;

}
