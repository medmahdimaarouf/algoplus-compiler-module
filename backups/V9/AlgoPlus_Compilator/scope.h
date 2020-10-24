#ifndef SCOPE_H
#define SCOPE_H
#include<iostream>
#include<QDebug>
#include<map>
#include<typeinfo>
#include "coreAlgo.h"

class Scope : public ObjectAlgo
{
public:
    Scope();
    Scope(const Scope &scope);
    Scope(QString name);

    void AddConstant(Constant constant);
    void AddType(Type *type);
    void AddVariable(Variable var);

    Constant getConstant(QString name);
    Type &getType(QString name);
    TypeOfContaint getTypeContaint(QString name);
    Variable getVariable(QString name);
    QList<Type *> getTypes()const;

    bool hasConstant(QString name){return listConstants->count(name);}
    bool hasType(QString name)    {return listTypes->count(name);}
    bool hasVariable(QString name){return listVariables->count(name);}
    void virtual CheckExistID(std::string id);// METHODE THROWS SYNTAXIC ERROR

    std::string toString();
    QString virtual whats(){return what;}

protected:

    QMap<QString,Constant>   * listConstants = NULL;
    QMap<QString,Variable>   * listVariables = NULL;
    std::map<QString,Type*>   * listTypes = NULL;
    //QMap<QString,Type>       * listTypes = NULL;
    Statment                 * Debut = NULL;
    QString what = "SCOPE";
};

#endif // SCOPE_H
