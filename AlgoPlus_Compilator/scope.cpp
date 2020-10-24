#include "scope.h"

Scope::Scope()
{

    this->listConstants = new MapConstantes();
    this->listTypes     = new MapTypes;
    this->listVariables = new MapVariables();
    Debut = new Statment();
}

Scope::Scope(const Scope &scope):Scope()
{
    ListTypes listTypes = scope.getTypes();
    for(ListTypes::iterator i = listTypes.begin(); i != listTypes.end();i++)
    {
        AddType(*i);
    }
    ListConstantes listConstants = scope.getConstants();
    for(ListConstantes::iterator i = listConstants.begin(); i != listConstants.end();i++)
    {
        AddConstant(*i);
    }
}

Scope::Scope(StdString name):ObjectAlgo(name)
{

}

Constant Scope::getConstant(StdString name)
{
    if(hasConstant(name))
       throw  "Constante '" + name + "' n'existe pas ";
    else
      return listConstants->at(name);
}

Type & Scope::getType(StdString name)
{
    if(this->hasType(name))
        return *listTypes->at(name);
    else
         throw "Type '" + name + "'' n'existe pas ";
}

TypeOfContaint Scope::getTypeContaint(StdString name)
{
    if(hasType(name))
        return TypeOfContaint(name);
    else
        throw "Type '" + name  + "' n est pas declare dans ce programme ";
}

Variable Scope::getVariable(StdString name)
{
    if(hasVariable(name))
        return listVariables->at(name);
    else
        throw "Variable '" + name + "' n'existe pas";
}

ListConstantes Scope::getConstants() const
{
    ListConstantes list;
    for(MapConstantes::iterator it = this->listConstants->begin();
        it != this->listConstants->end();
        ++it)
    {
        list.push_back(it->second);
    }
    return list;
}

ListTypes Scope::getTypes() const
{
    ListTypes list;
    for(MapTypes::iterator it = this->listTypes->begin(); it != this->listTypes->end();++it)
    {
        list.push_back(it->second);
    }
    return list;
}

ListVaribles Scope::getListVariables() const
{
    ListVaribles list;
    for(MapVariables::iterator it = this->listVariables->begin(); it != this->listVariables->end();++it)
    {
        list.push_back(it->second);
    }
    return list;
}

void Scope::AddConstant(Constant constant)throw()
{
    this->CheckExistID(constant.getName() );
    if(listConstants->count(constant.getName()))
       throw  "Constante '" + constant.getName()  + "' existe deja ";
    else
       listConstants->insert(std::make_pair<StdString,Constant>(constant.getName(),constant));
}

void Scope::AddType(Type *type)
{
    this->CheckExistID(type->getName() );
    if(!this->hasType(type->getName()))
        this->listTypes->insert(std::make_pair(type->getName(),type));
    else
        throw "Type '" + type->getName()  + "' existe deja ";
}

void Scope::AddVariable(Variable var)
{
    this->CheckExistID(var.getName() );
    if(hasVariable(var.getName()))
        throw "Variable '" + var.getName()  + "' existe deja ";
    else
        this->listVariables->insert(std::pair<StdString,Variable>(var.getName(),var));
}

void Scope::CheckExistID(StdString id)
{
    if(id == ""){
        //? CHECK THAT?
    }
    else
    if(id.toUpper() == name)
        throw "'" + id + "'deja declare comme le nom du programme ";
    else
    if(this->hasConstant(id.toUpper()))
        throw "'" + id + "' est un constante deja declare";
    else
    if(this->hasType(id.toUpper()))
        throw "'" + id + "' est un type deja declare";
    else
    if(this->hasVariable(id.toUpper()))
        throw "'" + id + "' est un variable deja declare";

}

StdString Scope::toString()
{

    StdString desc = "\n CONSTANTES \n";
    for(MapConstantes::iterator i = listConstants->begin(); i != listConstants->end();i++)
    {
        desc += "\t \t";
        Constant s = i->second;
        desc += s.toString() + "\n";
    }
    desc += "\n TYPES \n";
    for(MapTypes::iterator i = listTypes->begin(); i != listTypes->end();i++)
    {
        desc += "\t \t";
        Type * T = i->second;
        if(dynamic_cast<RecordType*>(T))
        {
            desc += dynamic_cast<RecordType*>(T)->toString() +  "\n";
        }
        else
        if(dynamic_cast<Array*>(T))
        {
            desc += dynamic_cast<Array*>(T)->toString() + "\n";
        }
        else
        if(dynamic_cast<MatrixType*>(T))
        {
            desc += dynamic_cast<MatrixType*>(T)->toString() + "\n";
        }
        else
        if(dynamic_cast<FileType*>(T))
        {
            desc += dynamic_cast<FileType*>(T)->toString() + "\n";
        }
        else
        {
            //desc +="NO casting" + T->toString()+ "to String typr id " + StdString(typeid(*T).name()) +"\n";
            desc += T->toString() + "\n";
        }
    }
    desc += "\n VARIABLES \n";
    for(MapVariables::iterator i = listVariables->begin(); i != listVariables->end();i++)
    {
        desc += "\t \t";
        Variable v = i->second;
        desc += v.toString() + "\n";
    }
    desc += "\n DEBUT \n";
    desc += Debut->toString();
    desc += "\n\n END. \n" ;

    return desc;
}
