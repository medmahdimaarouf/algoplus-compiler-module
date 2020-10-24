#include "mainscope.h"
#include<function.h>
#include<QDebug>
MainScope::MainScope():Scope()
{
    this->listFunctions = new std::map<QString,Function*>();
    this->listProcedures = new std::map<QString,Procedure*>();

    Type * T1 = new Type("ENTIER");
    this->AddType(T1);
    Type * T2 = new Type("REEL");
    this->AddType(T2);
    Type * T3 = new Type("CHAINE");
    this->AddType(T3);
    Type * T4 = new Type("CARACTERE");
    this->AddType(T4);
    Type * T5 = new Type("BOOLEEN");
    this->AddType(T5);

}

MainScope::MainScope(QString name):MainScope()
{
    setName(name);
}

bool MainScope::hasFunction(QString name)
{
    return this->listFunctions->count(name);
}

bool MainScope::hasProcedure(QString name)
{
    return this->listProcedures->count(name);
}

void MainScope::AddFunction(Function &function)
{
    CheckExistID(function.getName().toStdString());
    this->listFunctions->insert(std::pair<QString,Function*>(function.getName(),&function));
}

void MainScope::AddProcedure(Procedure &prcoedure)
{
    CheckExistID(prcoedure.getName().toStdString());
    this->listProcedures->insert(std::pair<QString,Procedure*>(prcoedure.getName(),&prcoedure));
}

Function &MainScope::getFunction(QString name)
{
    if(hasFunction(name))
        return *this->listFunctions->at(name);
    else
        throw "La fonction '" + name.toStdString() + "' n est pas declare dans ce programme";
}

Procedure &MainScope::getProcedure(QString name)
{
    if(hasProcedure(name))
        return *this->listProcedures->at(name);
    else
        throw "La procedure '" + name.toStdString() + "' n est pas declare dans ce programme";
}

void MainScope::CheckExistID(std::string id)
{
    if(hasFunction(QString::fromStdString(id).toUpper()))
        throw "'" + id + "' deja declarer comme une fonction ";
    else
    if(hasProcedure(QString::fromStdString(id).toUpper()))
        throw "'" + id + "' deja declarer comme une procedure ";
    this->Scope::CheckExistID(id);
}

std::string MainScope::toString()
{
    std::string desc ;//= "\n CONSTANTES \n";
    desc += this->Scope::toString();
    for(std::map<QString,Function*>::iterator it = this->listFunctions->begin(); it != this->listFunctions->end();++it)
    {
        Function *p = it->second;
        desc += p->toString();

    }
    for(std::map<QString,Procedure*>::iterator it = this->listProcedures->begin(); it != this->listProcedures->end();++it)
    {
        Procedure *p = it->second;
        desc += p->toString();

    }

    return "ALGORITHME " + name.toStdString() + "\n " + desc;
}

void MainScope::Clear()
{
    this->listConstants->clear();
    this->listFunctions->clear();
    this->listProcedures->clear();
    this->listTypes->clear();
    this->listVariables->clear();
}

