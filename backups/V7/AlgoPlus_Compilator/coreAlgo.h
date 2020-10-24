#include<token.h>
#include<headerAlgo.h>
// + ----- EXPRESSIONS
class NodeExpression{
public:
    typedef struct ExpressionOperator{
        Token * value;
        NodeExpression * FirstOperand = NULL;
        NodeExpression * SecondOperand = NULL;
        int priority;
    }ExpressionOperator;

    NodeExpression(){}
    void virtual setReturnType(TypeOfContaint returntype){this->returnType = new TypeOfContaint(); *this->returnType = returntype;}
    NodeExpression * end(){return NULL;}
    void setExpressionOperator(ExpressionOperator *expressionOpertor){this->expressionOpertor = expressionOpertor;this->expressionOpertor->FirstOperand = this;}
    bool hasExpressionOperator(){return expressionOpertor != NULL;}
    bool hasReturnType(){return returnType == NULL;}
    ExpressionOperator*getExpressionOperator(){return this->expressionOpertor;}
    TypeOfContaint getReturnType(){return *returnType;}
    std::string virtual toString(){
        std::string std = "";
        
        if(hasExpressionOperator())
        {
                
        }
        
        return std;
    }
protected:
    TypeOfContaint *returnType = NULL;
    ExpressionOperator *expressionOpertor = NULL;

};

class NodeReference : public ObjectAlgo,public NodeExpression{
public:
    typedef struct ByteOperator{
        Token * value;
        NodeExpression * FirstOperand = NULL;
        NodeExpression * SecondOperand = NULL;
    }ByteOperator;

    NodeReference(){}
    void virtual setValue(Token *value){this->value = value;}
    void virtual setReturnType(TypeOfContaint returntype){this->returnType = new TypeOfContaint() ;*this->returnType = returntype;}
    void setByteOperator(ByteOperator *byteoperator){this->byteOperator = byteoperator;}
    bool hasByteOpertor(){return byteOperator != NULL;}
    Token*getValue(){return this->value;}
    TypeOfContaint getReturnType(){return *returnType;}
    ByteOperator*getByteOperator(){return this->byteOperator;}
    std::string toString(){
        std::string res = "";
        if(value != NULL)
        {
            res += value->Value();
            if(hasByteOpertor())
            {
                res += byteOperator->value->Value();
                res += byteOperator->SecondOperand->toString();
            }
        }
        return res;
    }

private:
    Token *value = NULL;
    ByteOperator   *byteOperator = NULL;
    TypeOfContaint *returnType = NULL;
};

typedef NodeReference Reference;

typedef NodeExpression Expression;

class ConstValue : public NodeExpression
{
public:
    ConstValue() {}
    ConstValue(Token *value) {this->setValue(value);}
    void setValue(Token *value){
        if(value->Nature() == Reel)
            this->returnType = new TypeOfContaint("REEL");
        else
        if(value->Nature() == NUMBER)
            this->returnType = new TypeOfContaint("ENTIER");
        else
        if(value->Nature() == STR)
             this->returnType = new TypeOfContaint("CHAINE");
        else
        if(value->Nature() == CHAR)
             this->returnType = new TypeOfContaint("CARACTERE");
        else
        if(value->Nature() == KeyWord && (value->Value() == "VRAI" || value->Value() == "FAUX"))
             this->returnType = new TypeOfContaint("BOOLEEN");
        else
            throw "invalide expression avec le mot '" + value->Value() + "'";
        this->value = value;
        }

    Token*getValue(){return this->value;}
    std::string toString(){
        std::string str = "";
        str = value->Value() + " " ;
        if(hasExpressionOperator())
            str +=  expressionOpertor->value->Value() + " ";
        return str;
    }

private:
    Token * value = NULL;

};

class FctCall : public NodeExpression,ObjectAlgo
{
public:
    FctCall(){}
    FctCall(std::string namefct):ObjectAlgo(QString::fromStdString(namefct)){}
    void AddEffectArg(Expression *arg){listEffctArgs.append(arg);}
    Expression* getEffectArg(int order){listEffctArgs.at(order);}
    bool hasEffectArgs(){return listEffctArgs.isEmpty();}
    std::string toString(){
        std::string res = "FN " + this->getName().toStdString() + " (";
        if(this->hasEffectArgs())
        {
            for(int i = 0; i< listEffctArgs.size();i++)
            {
                res += " " + listEffctArgs.at(i)->toString() + " ,";

            }
            res.replace(res.size() - 1 , 1," )");
        }

        return res;

    }

private:
    QList<Expression*> listEffctArgs;
};

// - ----- EXPRESSIONS
enum StatmentBehavio{
        Debut,ASSIGN,IF,ELSE,FOR,REPEAT,WHILE,CALL_PROCEDURE,With
};

class Statment {
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
    std::string toString(){
        std::string desc = "";
        if(hasChildStatments())
        {
            QList<Statment*> liststt = this->getChildStatments();
            for(int i = 0; i < liststt.size();i++)
                desc += liststt.at(i)->toString();
        }
        //return "empty statment !";
        return desc;
    }
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

class Case_Statment : public Statment
{
public:
    Case_Statment() {}
    void setCaseValue(std::string value_case){this->value_case = value_case;}
    std::string getCaseValue(){return value_case;}
private:
    std::string value_case;
};

class Swith_Statment : public Statment
{
public:
    Swith_Statment(){listCases = new std::list<Case_Statment*>();}
    Swith_Statment(Statment * parent):Statment(parent){listCases = new std::list<Case_Statment*>();}
private:
    std::list<Case_Statment*> *listCases;
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
