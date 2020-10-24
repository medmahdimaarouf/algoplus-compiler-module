#include "mainscope.h"
#include<function.h>
#include<QDebug>


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

    }catch(std::string error){
        std::cout<<"ADDING ECRIRE & LIRE : "<<error;
    }


}

MainScope::MainScope(std::string name):MainScope()
{
    setName(name);
}

bool MainScope::hasFunction(std::string name)
{
    return this->listFunctions->count(name);
}

bool MainScope::hasProcedure(std::string name)
{
    return this->listProcedures->count(name);
}

void MainScope::AddFunction(Function &function)
{
    CheckExistID(function.getName());
    this->listFunctions->insert(std::pair<std::string,Function*>(function.getName(),&function));
}

void MainScope::AddProcedure(Procedure &prcoedure)
{
    CheckExistID(prcoedure.getName());
    this->listProcedures->insert(std::pair<std::string,Procedure*>(prcoedure.getName(),&prcoedure));
}

Function &MainScope::getFunction(std::string name)
{
    if(hasFunction(name))
        return *this->listFunctions->at(name);
    else
        throw "La fonction '" + name + "' n est pas declare dans ce programme";
}

Procedure &MainScope::getProcedure(std::string name)
{
    if(hasProcedure(name))
        return *this->listProcedures->at(name);
    else
        throw "La procedure '" + name + "' n est pas declare dans ce programme";
}

void MainScope::CheckExistID(std::string id)
{
    if(hasFunction(toUpper(id)))
        throw "'" + id + "' deja declarer comme une fonction ";
    else
    if(hasProcedure(toUpper(id)))
        throw "'" + id + "' deja declarer comme une procedure ";
    this->Scope::CheckExistID(id);
}

std::string MainScope::toString()
{
    std::string desc ;//= "\n CONSTANTES \n";
    desc += this->Scope::toString();
    for(std::map<std::string,Function*>::iterator it = this->listFunctions->begin(); it != this->listFunctions->end();++it)
    {
        Function *p = it->second;
        desc += p->toString();

    }
    for(std::map<std::string,Procedure*>::iterator it = this->listProcedures->begin(); it != this->listProcedures->end();++it)
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

