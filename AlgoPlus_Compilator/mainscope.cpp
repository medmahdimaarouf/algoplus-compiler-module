#include "mainscope.h"
#include<function.h>


MainScope::MainScope():Scope()
{
    this->listFunctions = new MapFunctions();
    this->listProcedures = new MapProcedures();

    Type * T1 = new Type("ENTIER",true);
    this->AddType(T1);
    Type * T2 = new Type("REEL");
    this->AddType(T2);
    Type * T3 = new Type("CHAINE");
    this->AddType(T3);
    Type * T4 = new Type("CARACTERE",true);
    this->AddType(T4);
    Type * T5 = new Type("BOOLEEN",true);
    this->AddType(T5);

    try{

        Procedure * ecrire = new Procedure(*this);
        ecrire->setName("ECRIRE");
        AddProcedure(*ecrire);

        Procedure * lire = new Procedure(*this);
        lire->setName("LIRE");
        AddProcedure(*lire);

        Procedure * allouer = new Procedure(*this);
        allouer->setName("ALLOUER");
        AddProcedure(*allouer);

        Procedure * liberer = new Procedure(*this);
        liberer->setName("LIBERER");
        AddProcedure(*liberer);

    }catch(StdString error){
        std::cout<<"ADDING ECRIRE & LIRE : "<<error.toStdString();
    }


}

MainScope::MainScope(StdString name):MainScope()
{
    setName(name);
}

bool MainScope::hasFunction(StdString name)
{
    return this->listFunctions->count(name);
}

bool MainScope::hasProcedure(StdString name)
{
    return this->listProcedures->count(name);
}

void MainScope::AddFunction(Function &function)
{
    CheckExistID(function.getName());
    this->listFunctions->insert(std::pair<StdString,Function*>(function.getName(),&function));
}

void MainScope::AddProcedure(Procedure &prcoedure)
{
    CheckExistID(prcoedure.getName());
    this->listProcedures->insert(std::pair<StdString,Procedure*>(prcoedure.getName(),&prcoedure));
}

Function &MainScope::getFunction(StdString name)
{
    if(hasFunction(name))
        return *this->listFunctions->at(name);
    else
        throw "La fonction '" + name + "' n est pas declare dans ce programme";
}

Procedure &MainScope::getProcedure(StdString name)
{
    if(hasProcedure(name))
        return *this->listProcedures->at(name);
    else
        throw "La procedure '" + name + "' n est pas declare dans ce programme";
}

void MainScope::CheckExistID(StdString id)
{
    if(hasFunction(id.toUpper()))
        throw "'" + id + "' deja declarer comme une fonction ";
    else
    if(hasProcedure(id.toUpper()))
        throw "'" + id + "' deja declarer comme une procedure ";
    this->Scope::CheckExistID(id);
}

StdString MainScope::toString()
{
    StdString desc ;//= "\n CONSTANTES \n";
    desc += this->Scope::toString();
    for(std::map<StdString,Function*>::iterator it = this->listFunctions->begin(); it != this->listFunctions->end();++it)
    {
        Function *p = it->second;
        desc += p->toString();

    }
    for(std::map<StdString,Procedure*>::iterator it = this->listProcedures->begin(); it != this->listProcedures->end();++it)
    {
        Procedure *p = it->second;
        desc += p->toString();

    }

    return "ALGORITHME " + name + "\n " + desc;
}

void MainScope::Clear()
{
    this->listConstants->clear();
    this->listFunctions->clear();
    this->listProcedures->clear();
    this->listTypes->clear();
    this->listVariables->clear();
}

