#include<QString>
#include<QMap>

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


//** PARENT TYPE CLASS
class ObjectAlgo{
public:
    ObjectAlgo(){}
    ObjectAlgo(QString name){this->setName(name.toUpper());}
    void virtual setName(QString name){this->name = name;}
    QString virtual getName()const{return name;}
    std::string virtual toString(){return "ABSTRACT OBJECT ALGO : " + name.toStdString();}
protected:
    QString name;
};

enum TypeBehavior{
    DEFAULT,RECOED,ARRAY,MATRICE,_FILE,QALIFIER
};

class Type : public ObjectAlgo{
public:
    Type(){}
    Type(QString name):ObjectAlgo(name){}
    Type * self(){return this;}
    /*
    void addMemoryRange(){memoryRange++;}
    void addMemoryRange(int range){this->memoryRange = range;}
    int getMemoryRange()const{return memoryRange;}
    */
    std::string toString(){return "\n\t" + name.toStdString() + " = DEFAULT TYPE ";}
    TypeBehavior virtual Is(){return DEFAULT;}
private:
    //int unsigned  memoryRange = 0;
    TypeBehavior behavior;
};

class TypeOfContaint : public ObjectAlgo
{
public:
    TypeOfContaint(){}
    TypeOfContaint(QString name):ObjectAlgo(name) {}
    void addMemoryRange(){memoryRange++;}
    void addMemoryRange(int range){this->memoryRange = range;}
    int getMemoryRange()const{return memoryRange;}
private:
    int unsigned  memoryRange = 0;
};


/// *****************************************************************************************
///                             HEADER ALGO
/// *****************************************************************************************
// ** CONST CLASS
class Constant : public ObjectAlgo{
public:
    Constant(){}
    Constant(QString name):ObjectAlgo(name){}
    Constant(QString name,QString value,Type typeValue):ObjectAlgo(name){setValue(value);setTypeValue(typeValue);}
    void setValue(QString value){
        this->value = value;
    }
    QString getValue(){return value;}
    void setTypeValue(const Type type){typeValue = type;}
    Type getTypeValue(){return typeValue;}
    std::string toString(){return "\n\t" + name.toStdString() + "=" + value.toStdString();}
private:
    QString value;
    Type typeValue;

};

//** ARRAY CLASS
class Array      : public Type {
public:
     Array(){}
     Array(QString name):Type(name){}
     Array(QString name,TypeOfContaint typeContaint,int size):Type(name){this->setTypeContaint(typeContaint);this->setSize(size);}
     void setSize(int size){this->size = size;}
     void setTypeContaint(TypeOfContaint typeContaint){this->typeContaint = typeContaint;}
     int getSize(){return this->size;}
     TypeOfContaint getTypeContaint(){return this->typeContaint;}
     TypeBehavior Is(){return ARRAY;}
     std::string toString(){
         std::string tt = "";
         for(int i = 0; i < this->typeContaint.getMemoryRange();i++)
             tt += "@";
         return "\n\t" + this->getName().toStdString() + " = ARRAY[1.." + QString::number(size).toStdString() + "] OF " + tt + typeContaint.getName().toStdString();
     }
private:
    int size;
    TypeOfContaint typeContaint;
};
//** MATRIX TYPE CLASS
class MatrixType : public Type{
public:
     MatrixType(QString name):Type(name){}
     MatrixType(QString name,int columnsCount,int rowsCount,TypeOfContaint typeContaint):Type(name){setColumnsCount(columnsCount);setRowsCount(rowsCount);setTypeContaint(typeContaint);}
     void setColumnsCount(int columnsCount){this->columnsCount = columnsCount;}
     void setRowsCount(int rowsCount){this->rowsCount = rowsCount;}
     void setTypeContaint(TypeOfContaint typeContaint){this->typeContaint = typeContaint;}
     TypeOfContaint getTypeContaint(){return this->typeContaint;}
     int getColumnsCount(){return this->columnsCount;}
     int getRowsCount(){return this->rowsCount;}
     TypeBehavior Is(){return MATRICE;}
     std::string toString(){
         std::string tt = "";
         for(int i = 0; i < this->typeContaint.getMemoryRange();i++)
             tt += "@";

         return "\n\t" + this->getName().toStdString() + " = ARRAY[1.." + QString::number(rowsCount).toStdString() + ",1.." + QString::number(columnsCount).toStdString() + " ] OF " + tt + typeContaint.getName().toStdString();
     }

private:
     int columnsCount;
     int rowsCount;
     TypeOfContaint typeContaint;
};

// ** RECORD TYPE
typedef struct FieldRecord{
    QString nom;
    TypeOfContaint type;
}fieldRecord;

class RecordType : public Type{
public:
    RecordType(){this->Fields = new QMap<QString,FieldRecord>();}
    RecordType(QString name):Type(name){RecordType();}
    ~RecordType(){this->Fields = NULL;}
    void AddField(FieldRecord field){if(this->Fields->contains(field.nom)) throw "Champ '" + field.nom +"' existe deja"; else Fields->insert(field.nom,field);}
    void setFields(QMap<QString,FieldRecord> * Fields){this->Fields = Fields;}
    QMap<QString,FieldRecord> * getFields(){return this->Fields;}
    TypeBehavior Is(){return RECOED;}
    std::string toString(){
        std::string fields = "";
        for(int i = 0; i < Fields->size();i++)
        {
            std::string tt = "";
            for(int j = 0; j < this->Fields->values().at(i).type.getMemoryRange();j++)
                tt += "@";

            fields += "\n\t\t" + Fields->values().at(i).nom.toStdString() + ":" + tt + Fields->values().at(i).type.getName().toStdString();
        }
        return "\n\t" + this->getName().toStdString() + " = RECORD " + fields + "\n\tEND RECORD";
    }

private:
    QMap<QString,FieldRecord>* Fields;
};

// ** FILE CLASS TYPE
class FileType   : public Type{
public:
    FileType(QString name):Type(name){}
    FileType(QString name,TypeOfContaint typeContaint):Type(name){setTypeContaint(typeContaint);}
    TypeOfContaint getTypeContaint(){return this->typeContaint;}
    void setTypeContaint(TypeOfContaint typeContaint){this->typeContaint = typeContaint;}
    TypeBehavior Is(){return _FILE;}
    std::string toString(){
        std::string tt = "";
        for(int i = 0; i < typeContaint.getMemoryRange();i++)
            tt += "@";
        return "\n\t" + this->getName().toStdString() + " = FILE OF " + tt +typeContaint.getName().toStdString();}
private:
    TypeOfContaint typeContaint;
};

class QalifierType : public Type
{
public:
    QalifierType(QString name):Type(name){}
    QalifierType(QString name,TypeOfContaint typeQalified):Type(name){this->typeQalified = typeQalified;}
    TypeOfContaint getTypeQalified(){return this->typeQalified;}
    void setTypeQalified(TypeOfContaint typeQalified){this->typeQalified = typeQalified;}
    TypeBehavior Is(){return QALIFIER;}
    std::string toString(){
        std::string tt = "";
        for(int i = 0; i < typeQalified.getMemoryRange();i++)
            tt += "@";
        return "\n\t" + this->getName().toStdString() + " = " + tt +typeQalified.getName().toStdString();}
private:
    TypeOfContaint typeQalified;

};
// *** VARIABLE CLASS
class Variable : public ObjectAlgo{
public:
    Variable(){}
    Variable(QString name,TypeOfContaint type):ObjectAlgo(name){setType(type);}
    void setType(TypeOfContaint type){this->type = type;}
    TypeOfContaint getType(){return type;}
    std::string toString(){
        std::string tt = "";
        for(int i = 0; i < type.getMemoryRange();i++)
            tt += "@";
        return "\n\t " + getName().toStdString() + ":" + tt + type.getName().toStdString();
    }
protected:
    QString name;
    TypeOfContaint type;
};

enum IOArgment{
    IN,OUT,IN_OUT
};

class Argment: public Variable{
public:
    Argment(){}
    Argment(QString name,TypeOfContaint type,IOArgment io):Variable(name,type){this->io = io;}
    void setIO(IOArgment io){this->io = io;}
    IOArgment getIO(){return this->io;}
    std::string toString(){
        std::string tt = "";
        for(int i = 0; i < type.getMemoryRange();i++)
            tt += "@";
        if(io == IN)
            return "IN  " + this->getName().toStdString() + ":" + tt + type.getName().toStdString();
        else
        if(io == OUT)
            return "OUT  " + this->getName().toStdString() + ":" + tt + type.getName().toStdString();
        else
            return "IN_OUT  " + this->getName().toStdString() + ":" + tt + type.getName().toStdString();
    }
private:
    IOArgment io;
};

/// *****************************************************************************************
///                                  CORE ALGO
/// *****************************************************************************************
enum OperatorType{
    AND,OR,XOR,NOT,EQUAL,LE,GE,GRAND,LESS,PLUS,SUB,MULT,DIV,MOD
};

class Operator : private ObjectAlgo{
public:
    //Operator(){}
    Operator(std::string name,OperatorType Nature):ObjectAlgo(QString::fromStdString(name)){this->Nature = Nature;}
private:
    OperatorType Nature;
};

class Expression : private ObjectAlgo {
public:
    Expression(){}
    TypeOfContaint returnType(){}
    bool HasOperator(){return Operator == NULL;}
    bool HasSecondArg(){return SecondArg == NULL;}
private:
    int priority;
    Expression * firstArg;
    Expression * SecondArg = NULL;
    std::string *Operator = NULL;
    std::string value;


};


enum StatmentBehavio{
        Debut,ASSIGN,IF,ELSE,FOR,REPEAT,WHILE,CALL_PROCEDURE,With
};

class Statment : public ObjectAlgo {
public :
    Statment(){this->childStatments = new QList<Statment*>;}
    Statment(Statment * parent){SetParent(parent);Statment();}
    Statment(Statment * parent,StatmentBehavio behavior){SetBehavior(behavior);SetParent(parent);Statment();}
    void addChildStatment(Statment *st){st->SetParent(this); *this->childStatments << st;}
    void SetParent(Statment * parent){if(parent)this->parent = parent;}
    void SetBehavior(StatmentBehavio behavior){this->behavior = behavior;}
    StatmentBehavio GetBehavior(){return behavior;}
    Statment* GetParent(){return parent;}
    bool hasChildStatments(){return !this->childStatments->isEmpty();}
    QList<Statment*>  getChildStatments(){return *this->childStatments;}
    std::string toString(){return "empty statment !";}
protected:
    Statment * parent = __null;
    StatmentBehavio behavior;
    QList<Statment*>  * childStatments;
};

class IF_Statment : public Statment
{
public:
    IF_Statment():Statment(){}
    IF_Statment(Statment * parent):Statment(parent){}
    IF_Statment(Expression condition){this->setCondition(condition);}
    Expression getCondition(){return this->condition;}
    void setCondition(Expression condition){this->condition = condition;}
private:
    Expression condition;
};
// Recferance | variable | valeur
class For_Statment : public Statment
{
public:
    For_Statment(){}
    For_Statment(Statment * parent):Statment(parent){}
    Expression * getVi(){return vi;}
    Expression * getVf(){return vf;}
    Expression * getCompter(){return c;}
    Expression * getStep(){return this->step;}
    void setVf(Expression * vf){this->vf = vf;}
    void setVi(Expression * vi){this->vi = vi;}
    void setCompter(Expression * compter){this->c = compter;}
    void setStep(Expression *step){this->step =step;}
private:
    Expression *vi = NULL;
    Expression *vf = NULL;
    Expression *c  = NULL;
    Expression *step= NULL;
};
class While_Statment : public Statment
{
public:
    While_Statment(){}
    While_Statment(Statment * parent):Statment(parent){}
    Expression getCondition(){return this->condition;}
    void setCondition(Expression condition){this->condition = condition;}
private:
    Expression condition;
};
class Repeat_Statment : public Statment
{
public:
    Repeat_Statment(){}
    Repeat_Statment(Statment * parent):Statment(parent){}
    Expression getCondition(){return this->condition;}
    void setCondition(Expression condition){this->condition = condition;}
private:
    Expression condition;
};
class Swith_Statment : public Statment
{
public:
    Swith_Statment(){}
    Swith_Statment(Statment * parent):Statment(parent){}
private:
    // nothing
};

class CallProc_Statment : public Statment
{
public:
    CallProc_Statment() {}
    CallProc_Statment(Statment * parent):Statment(parent) {}
};
























/*enum TermBehavior{
    Number,Real,Str,Char,Boolean,id_var,Fielding,Indexing,FctCall
};

class Term : public ObjectAlgo {
private:
    Term(TermBehavior behavior){}
    void GetBehavior(){return behavior;}
    TermBehavior setBehavior(TermBehavior Behavior){this->behavior = Behavior;}
public:
    TermBehavior behavior;
};
*/
