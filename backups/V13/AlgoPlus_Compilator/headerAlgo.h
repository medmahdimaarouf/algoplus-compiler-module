
///------------- STATMENTS XML DOM INDEXING ------
#define XML_REPEATE -1
#define XML_END      0
#define XML_ASSIGN   1
#define XML_READ     2
#define XML_WRITE    3
#define XML_COMMENT  4
#define XML_IF       5
#define XML_ELSE     6
#define XML_SWITCH   7
#define XML_CASE     8
#define XML_FOR      9
#define XML_WHILE   10
#define XML_UNTIL   11
#define XML_CALL    12
#define XML_RETURN  13
///----------------- -----------------------------

#ifndef STRING_OPERATIONS
#include "stringOperations.h"
#endif

class ObjectAlgo{
public:
    ObjectAlgo(){}
    ObjectAlgo(std::string name){this->setName(toUpper(name));}
    void virtual setName(std::string name){this->name = name;}
    std::string virtual getName()const{return name;}
    std::string virtual toString(){return "ABSTRACT OBJECT ALGO : " + name ;}
    bool virtual operator ==(ObjectAlgo other){if(this->getName() == other.getName()) return true;else return false;}
    bool virtual operator !=(ObjectAlgo other){if(this->getName() != other.getName()) return true;else return false;}
public:
    std::string name;
};

enum TypeBehavior{
    DEFAULT,RECOED,ARRAY,MATRICE,_FILE,QALIFIER
};

class Type : public ObjectAlgo{
public:
    Type(){}
    Type(std::string name):ObjectAlgo(name){}
    Type(std::string name,const bool scalar):ObjectAlgo(name){setScalar(scalar);}
    Type * self(){return this;}
    std::string toString(){return "\n\t" + name + " = DEFAULT TYPE ";}
    TypeBehavior virtual Is(){return DEFAULT;}
    void setScalar(const bool scalar){this->scalar = scalar;}
    bool isScalar()const{return scalar;}
    bool operator ==(Type other){return this->getName() == other.getName() && this->behavior == other.Is();}
    bool operator !=(Type other){return this->operator ==(other) == false;}
private:
    TypeBehavior behavior;
    bool scalar = false;
};

class TypeOfContaint : public ObjectAlgo
{
public:
    TypeOfContaint(){}
    TypeOfContaint(std::string name):ObjectAlgo(name) {}
    void addMemoryRange(){memoryRange++;}
    void addMemoryRange(int range){this->memoryRange = range;}
    int getMemoryRange()const{return memoryRange;}

    bool operator ==(TypeOfContaint other) {return this->getName() == other.getName() && this->getMemoryRange() == other.getMemoryRange();}
    bool operator !=(TypeOfContaint other){return this->operator ==(other) == false;}
private:
    int unsigned  memoryRange = 0;
};


/// *****************************************************************************************
///                             HEADER ALGO
/// *****************************************************************************************

class Constant : public ObjectAlgo{
public:
    Constant(){}
    Constant(std::string name):ObjectAlgo(name){}
    Constant(std::string name,std::string value,Type typeValue):ObjectAlgo(name){setValue(value);setTypeValue(typeValue);}
    void setValue(std::string value){
        this->value = value;
    }
    std::string getValue(){return value;}
    void setTypeValue(const Type type){typeValue = type;}
    Type getTypeValue(){return typeValue;}
    std::string toString(){return "\n\t" + name + "=" + value;}
private:
    std::string value;
    Type typeValue;
};

//** ARRAY CLASS
class Array      : public Type {
public:
     Array(){}
     Array(std::string name):Type(name){}
     Array(std::string name,TypeOfContaint typeContaint,int size):Type(name){this->setTypeContaint(typeContaint);this->setSize(size);}
     void setSize(int size){this->size = size;}
     void setTypeContaint(TypeOfContaint typeContaint){
        if(!typeContaint.getMemoryRange() && name == typeContaint.getName())
            throw "Le tableu '" + name + "' a un type de contenu incomplete ";
        else
         this->typeContaint = typeContaint;
     }
     int getSize(){return this->size;}
     TypeOfContaint getTypeContaint(){return this->typeContaint;}
     TypeBehavior Is(){return ARRAY;}
     std::string toString(){
         std::string tt = "";
         for(int i = 0; i < this->typeContaint.getMemoryRange();i++)
             tt += "@";
         return "\n\t" + this->getName() + " = ARRAY[1.." + Number(size) + "] OF " + tt + typeContaint.getName();
     }
private:
    unsigned int size;
    TypeOfContaint typeContaint;
};
//** MATRIX TYPE CLASS
class MatrixType : public Type{
public:
     MatrixType(std::string name):Type(name){}
     MatrixType(std::string name,int columnsCount,int rowsCount,TypeOfContaint typeContaint):Type(name){setColumnsCount(columnsCount);setRowsCount(rowsCount);setTypeContaint(typeContaint);}
     void setColumnsCount(int columnsCount){this->columnsCount = columnsCount;}
     void setRowsCount(int rowsCount){this->rowsCount = rowsCount;}
     void setTypeContaint(TypeOfContaint typeContaint){
         if(!typeContaint.getMemoryRange() && name == typeContaint.getName())
            throw "La Matrice '" + name + "' a un type de contenu incomplete ";
         else
            this->typeContaint = typeContaint;
     }
     TypeOfContaint getTypeContaint(){return this->typeContaint;}
     int getColumnsCount(){return this->columnsCount;}
     int getRowsCount(){return this->rowsCount;}
     TypeBehavior Is(){return MATRICE;}
     std::string toString(){
         std::string tt = "";
         for(int i = 0; i < this->typeContaint.getMemoryRange();i++)
             tt += "@";

         return "\n\t" + this->getName() + " = ARRAY[1.." + Number(rowsCount) + ",1.." + Number(columnsCount) + " ] OF " + tt + typeContaint.getName();
     }

private:
     unsigned int columnsCount;
     unsigned int rowsCount;
     TypeOfContaint typeContaint;
};

// ** RECORD TYPE
typedef struct FieldRecord{
    std::string nom;
    TypeOfContaint type;
}fieldRecord;

class RecordType : public Type{
public:
    typedef std::map<std::string,FieldRecord> MapRecordFields;
    RecordType(){this->recordFields = new MapRecordFields();}
    RecordType(std::string name):Type(name){this->recordFields = new MapRecordFields();}
    ~RecordType(){this->recordFields = NULL;}
    void AddField(FieldRecord field){
        if(hasField(field.nom))
            throw "Le champ '" + field.nom +"' existe deja";
        else
        if(!field.type.getMemoryRange() && field.type.getName() == name)
            throw "Le champ '" + field.nom + "' a un type de contenu incomplete ";
        else
            recordFields->insert(std::make_pair<std::string,FieldRecord>(field.nom,field));
    }
    void setFields(MapRecordFields * Fields){this->recordFields = Fields;}
    MapRecordFields * getFields(){return this->recordFields;}
    TypeBehavior Is(){return RECOED;}
    std::string toString(){
        std::string stringfields = "";
        for(MapRecordFields::iterator i = recordFields->begin(); i != recordFields->end();i++)
        {
            std::string tt = "";
            FieldRecord field = i->second;
            for(int j = 0; j < field.type.getMemoryRange();j++)
                tt += "@";

            stringfields += "\n\t\t" + field.nom + ":" + tt + field.type.getName();
        }
        return "\n\t" + this->getName() + " = RECORD " + stringfields + "\n\tEND RECORD";
    }
    bool hasField(std::string name)const{return recordFields->count(name);}
private:
    MapRecordFields * recordFields;
};

// ** FILE CLASS TYPE
class FileType   : public Type{
public:
    FileType(std::string name):Type(name){}
    FileType(std::string name,TypeOfContaint typeContaint):Type(name){setTypeContaint(typeContaint);}
    TypeOfContaint getTypeContaint(){return this->typeContaint;}
    void setTypeContaint(TypeOfContaint typeContaint){
        if(!typeContaint.getMemoryRange() && name == typeContaint.getName())
            throw "La fichier '" + name + "' a un type de contenu incomplete ";
        else
        if(typeContaint.getName() == "TEXTE" && typeContaint.getMemoryRange())
            throw "Type de fichier texte incorrecte 'utilisation pointeur invalide '";
        else
            this->typeContaint = typeContaint;
    }
    bool IsTextFile(){return this->typeContaint.getName() == "TEXTE";}
    TypeBehavior Is(){return _FILE;}
    std::string toString(){
        std::string tt = "";
        for(int i = 0; i < typeContaint.getMemoryRange();i++)
            tt += "@";
        return "\n\t" + this->getName() + " = FILE OF " + tt +typeContaint.getName();}
private:
    TypeOfContaint typeContaint;
};

class AliasType : public Type
{
public:
    AliasType(std::string name):Type(name){}
    AliasType(std::string name,TypeOfContaint typeQalified):Type(name){this->typeQalified = typeQalified;}
    TypeOfContaint getTypeQalified(){return this->typeQalified;}
    void setTypeQalified(TypeOfContaint type_Qalified){
        if(!type_Qalified.getMemoryRange() && name == type_Qalified.getName())
            throw "Le tableu '" + name + "' a un type de contenu incomplete ";
        else
            this->typeQalified = type_Qalified;
    }
    TypeBehavior Is(){return QALIFIER;}
    std::string toString(){
        std::string tt = "";
        for(int i = 0; i < typeQalified.getMemoryRange();i++)
            tt += "@";
        return "\n\t" + this->getName() + " = " + tt +typeQalified.getName();}
private:
    TypeOfContaint typeQalified;

};
// *** VARIABLE CLASS
class Variable : public ObjectAlgo{
public:
    Variable(){}
    Variable(std::string name,TypeOfContaint type):ObjectAlgo(name){setType(type);}
    void setType(TypeOfContaint type){this->type = type;}
    TypeOfContaint getType(){return type;}
    std::string toString(){
        std::string tt = "";
        for(int i = 0; i < type.getMemoryRange();i++)
            tt += "@";
        return "\n\t " + getName() + ":" + tt + type.getName();
    }
protected:
    TypeOfContaint type;
};

enum IOArgment{
    IN,OUT,IN_OUT
};

class Argment: public Variable{
public:
    Argment(){}
    Argment(std::string name,TypeOfContaint type,IOArgment io):Variable(name,type){this->io = io;}
    void setIO(IOArgment io){this->io = io;}
    IOArgment getIO(){return this->io;}
    std::string toString(){
        std::string tt = "";
        for(int i = 0; i < type.getMemoryRange();i++)
            tt += "@";
        if(io == IN)
            return "IN  " + this->getName() + ":" + tt + type.getName();
        else
        if(io == OUT)
            return "OUT  " + this->getName() + ":" + tt + type.getName();
        else
            return "IN_OUT  " + this->getName() + ":" + tt + type.getName();
    }
private:
    IOArgment io;
};

/// *****************************************************************************************
///                                  CORE ALGO
/// *****************************************************************************************

