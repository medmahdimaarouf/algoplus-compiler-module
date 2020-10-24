#ifndef SCOPE_H
#define SCOPE_H
#include<iostream>
#include<QDebug>
#include<map>
#include<typeinfo>
#include "coreAlgo.h"

#ifndef MapTypes
typedef std::map<std::string,Type*>    MapTypes;
#endif
#ifndef MapConstantes
typedef std::map<std::string,Constant> MapConstantes;
#endif
#ifndef MapVariables
typedef std::map<std::string,Variable> MapVariables;
#endif
#ifndef ListTypes
typedef std::list<Type*>    ListTypes;
#endif
#ifndef ListConstantes
typedef std::list<Constant> ListConstantes;
#endif
#ifndef ListVaribles
typedef std::list<Variable> ListVaribles;
#endif


class Scope : public ObjectAlgo
{
public:
    Scope();
    Scope(const Scope &scope);
    Scope(std::string name);

    void AddConstant(Constant constant)throw();
    void AddType(Type *type);
    void AddVariable(Variable var);

    Constant getConstant(std::string name);
    Type &getType(std::string name);
    TypeOfContaint getTypeContaint(std::string name);
    Variable getVariable(std::string name);


    ListConstantes getConstants()const;
    ListTypes getTypes()const;
    ListVaribles getListVariables()const;
    Statment* getDebutStatment(){return Debut;}
    bool hasConstant(std::string name){return listConstants->count(name);}
    bool hasType(std::string name)    {return listTypes->count(name);}
    bool hasVariable(std::string name){return listVariables->count(name);}
    void setDebutStatment(Statment * Debut){this->Debut = Debut;}
    void virtual CheckExistID(std::string id);// METHODE THROWS SYNTAXIC ERROR

    std::string toString();
    std::string virtual whats(){return what;}

protected:

    MapConstantes  * listConstants = NULL;
    MapVariables   * listVariables = NULL;
    MapTypes       * listTypes     = NULL;
    Statment       * Debut         = NULL;
    std::string what = "SCOPE";
};

#endif // SCOPE_H
