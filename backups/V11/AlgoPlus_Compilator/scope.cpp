#include "scope.h"

Scope::Scope()
{

    this->listConstants = new QMap<QString,Constant>();
    //this->listTypes   = new QMap<QString,Type>();
    this->listTypes     = new std::map<QString,Type*>();
    this->listVariables = new QMap<QString,Variable>();
    Debut = new Statment();
}

Scope::Scope(const Scope &scope):Scope()
{
    //qDebug()<<" TYPE ID " <<QString(typeid(scope).name()) ;
    QList<Type*> list = scope.getTypes();
    for(int i = 0; i < list.size();i++)
    {
        Type *t = list.at(i);
        this->listTypes->insert(std::make_pair<QString,Type*>(t->getName(),t));
    }
    for(int i = 0; i < scope.listConstants->values().size();i++)
    {
        Constant c = scope.listConstants->values().at(i);
        this->listConstants->insert(c.getName(),c);
    }
}

Scope::Scope(QString name):ObjectAlgo(name)
{

}

Constant Scope::getConstant(QString name)
{
    if(listConstants->contains(name))
       throw  "Constante '" + name + "' n'existe pas ";
    else
      return listConstants->value(name);
}

Type & Scope::getType(QString name)
{
    //if(listTypes->contains(name))
     if(this->hasType(name))
        return *listTypes->at(name);
    else
         throw "Type '" + name.toStdString() + "'' n'existe pas ";
}

TypeOfContaint Scope::getTypeContaint(QString name)
{
    if(hasType(name))
        return TypeOfContaint(name);
    else
        throw "Type '" + name.toStdString() + "' n est pas declare dans ce programme ";
}

Variable Scope::getVariable(QString name)
{
    if(listVariables->contains(name))
        return listVariables->value(name);
    else
        throw "Variable '" + name + "' n'existe pas";
}

QList<Type*> Scope::getTypes() const
{
    QList<Type*> list;
    for(std::map<QString,Type*>::iterator it = this->listTypes->begin(); it != this->listTypes->end();++it)
    {
        list.append(it->second);
    }
    return list;
}

void Scope::AddConstant(Constant constant)
{
    this->CheckExistID(constant.getName().toStdString());
    if(listConstants->contains(constant.getName()))
       throw  "Constante '" + constant.getName().toStdString() + "' existe deja ";
    else
       listConstants->insert(constant.getName(),constant);
    //std::cout<< "CONST\tADDED :" + constant.toString()<<std::endl;
}

void Scope::AddType(Type *type)
{
    this->CheckExistID(type->getName().toStdString());
    if(!this->hasType(type->getName()))
        this->listTypes->insert(std::make_pair(type->getName(),type));
    else
        throw "Type '" + type->getName().toStdString() + "' existe deja ";
    //std::cout<<"TYPE\tADDED :" + type.toString() << std::endl;
    /* ************************************************************
     *
     *   THE CASTING IS WORKING CORRECTTLY HERE .
     *
     * ************************************************************/

    /*
    Type *f = type.self();
    if(static_cast<RecordType*>(f))
    {
        qDebug()<<"Adding type "<< QString::fromStdString( static_cast<RecordType*>(&type)->toString());
    }
    else
    if(static_cast<Array*>(f))
    {
        qDebug()<<"Adding type "<<QString::fromStdString( static_cast<Array*>(&type)->toString());
    }
    else
    if(static_cast<MatrixType*>(f))
    {
        qDebug()<<"Adding type "<<QString::fromStdString( static_cast<MatrixType*>(&type)->toString());
    }
    else
    if(static_cast<FileType*>(f))
    {
        qDebug()<<"Adding type "<<QString::fromStdString( static_cast<FileType*>(&type)->toString());
    }
    else
    {
        if(type.Is() != DEFAULT)
            qDebug()<<"Adding type NO casting "<< QString::fromStdString( type.toString())+ "\n";
        else
            qDebug()<<"Adding type "<< QString::fromStdString( type.toString())+ "\n";


    }
    */

}

void Scope::AddVariable(Variable var)
{
    this->CheckExistID(var.getName().toStdString());
    if(this->listVariables->contains(var.getName()))
        throw "Variable '" + var.getName().toStdString() + "' existe deja ";
    else
        this->listVariables->insert(var.getName(),var);
    //std::cout << "VAR\tADDED :" + var.toString() <<std::endl;
}

void Scope::CheckExistID(std::string id)
{
    if(QString::fromStdString(id).toUpper() == name)
        throw "'" + id + "'deja declare comme le nom du programme ";
    else
    if(this->hasConstant(QString::fromStdString(id).toUpper()))
        throw "'" + id + "' est un constante deja declare";
    else
    if(this->hasType(QString::fromStdString(id).toUpper()))
        throw "'" + id + "' est un type deja declare";
    else
    if(this->hasVariable(QString::fromStdString(id).toUpper()))
        throw "'" + id + "' est un variable deja declare";

}

std::string Scope::toString()
{

    std::string desc = "\n CONSTANTES \n";
    for(int i = 0; i < listConstants->values().size();i++)
    {
        desc += "\t \t";
        Constant s = listConstants->values().at(i);
        desc += s.toString() + "\n";
    }
    desc += "\n TYPES \n";
    for(int i = 0; i < this->getTypes().size();i++)
    {
        desc += "\t \t";
        Type *T = new Type();
        T = this->getTypes().at(i);
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
            //desc +="NO casting" + T->toString()+ "to string typr id " + QString(typeid(*T).name()).toStdString()+"\n";
            desc += T->toString() + "\n";
        }
    }
    desc += "\n VARIABLES \n";
    for(int i = 0; i < listVariables->values().size();i++)
    {
        desc += "\t \t";
        Variable v = listVariables->values().at(i);
        desc += v.toString() + "\n";
    }
    desc += "\n DEBUT \n";
    desc += Debut->toString();
    desc += "\n\n END. \n" ;
    //desc += "\n STATMENTS \n\t.\n\t.\n\t.\n END " + this->getName().toStdString() + "\n";

    return desc;
}
