#ifndef SCOPE_H
#define SCOPE_H
#include<iostream>
#include<map>
#include<typeinfo>
#include "coreAlgo.h"

#ifndef MapTypes
typedef std::map<StdString,Type*>    MapTypes;
#endif
#ifndef MapConstantes
typedef std::map<StdString,Constant> MapConstantes;
#endif
#ifndef MapVariables
typedef std::map<StdString,Variable> MapVariables;
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
    Scope(StdString name);

    void AddConstant(Constant constant)throw();
    void AddType(Type *type);
    void AddVariable(Variable var);

    Constant getConstant(StdString name);
    Type &getType(StdString name);
    TypeOfContaint getTypeContaint(StdString name);
    Variable getVariable(StdString name);


    ListConstantes getConstants()const;
    ListTypes getTypes()const;
    ListVaribles getListVariables()const;
    Statment* getDebutStatment(){return Debut;}
    bool hasConstant(StdString name){return listConstants->count(name);}
    bool hasType(StdString name)    {return listTypes->count(name);}
    bool hasVariable(StdString name){return listVariables->count(name);}
    void setDebutStatment(Statment * Debut){this->Debut = Debut;}
    void virtual CheckExistID(StdString id);// METHODE THROWS SYNTAXIC ERROR

    StdString toString();
    StdString virtual whats(){return what;}

protected:

    MapConstantes  * listConstants = NULL;
    MapVariables   * listVariables = NULL;
    MapTypes       * listTypes     = NULL;
    Statment       * Debut         = NULL;
    StdString what ;//= "SCOPE"; ******************************************************************************************
};

#endif // SCOPE_H
