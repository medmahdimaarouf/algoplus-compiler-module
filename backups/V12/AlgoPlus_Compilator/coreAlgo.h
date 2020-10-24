#include<token.h>
#include<headerAlgo.h>
//#include<stringOperations.h>

// + ----- EXPRESSIONS
class NodeExpression : public ObjectAlgo{
public:
    typedef struct ExpressionOperator {
        Token * value;
        NodeExpression * FirstOperand = NULL;
        NodeExpression * SecondOperand = NULL;
        int priority;
    }ExpressionOperator;
    // ADDED FOR SIGNEL OPERATORS EXPRESSIONS
    NodeExpression(){}
    void virtual setReturnType(TypeOfContaint returntype){this->returnType = new TypeOfContaint(); *this->returnType = returntype;}
    NodeExpression * end(){return NULL;}
    void setExpressionOperator(ExpressionOperator *expressionOpertor){this->expressionOpertor = expressionOpertor;this->expressionOpertor->FirstOperand = this;}
    bool hasExpressionOperator(){return expressionOpertor != NULL;}
    bool hasReturnType(){return returnType != NULL;}
    ExpressionOperator*getExpressionOperator(){return this->expressionOpertor;}
    TypeOfContaint getReturnType(){
        
        
        return *returnType;
    }
    std::string virtual toString(){
        std::string str = "";
        if(this->hasExpressionOperator())
        {
            str += " " + this->getExpressionOperator()->value->Value() + " " +  this->getExpressionOperator()->SecondOperand->toString();
        }

        return str;

    }

protected:
    TypeOfContaint *returnType = NULL;
    ExpressionOperator *expressionOpertor = NULL;

};

class Reference : public NodeExpression{
public:

    enum ByteOperatorbehavior{Undefined,MemberElementB_Opertor,IndexingB_Operator,MemoryRangeB_Operator};

    class ByteOperator : public ObjectAlgo{
    public:
        ByteOperator():ObjectAlgo("ByteOperator"){}
        ByteOperator(Token * value){setValue(value);}

        void setValue(Token * value){
            this->value == value;

            if(value->Nature() == LI)
                this->behavior = IndexingB_Operator;
            else
            if(value->Nature() == LocationSpecifier)
                this->behavior = MemoryRangeB_Operator;
            else
            if(value->Value() == ".")
                this->behavior = MemberElementB_Opertor;
            else
            {
                this->behavior = Undefined;
                perror("byte opertor value ambigue ");
                exit(1);
            }
        }
        void setNext(ByteOperator * next){this->Next = next;}//this->Next->setPrev(this);}
        void setPrev(ByteOperator * prev){this->Prev = prev;}
        void setArgment(NodeExpression * arg){this->argment = arg;}

        NodeExpression * getArgment(){return this->argment;}
        ByteOperator *getNext(){return this->Next;}
        ByteOperator *getPrev(){return this->Prev;}
        bool hasPrevOperator(){return this->Prev != NULL;}
        bool hasNextOperator(){return this->Next != NULL;}
        ByteOperatorbehavior getBehavior(){return behavior;}
        Token * getValue(){return this->value;}
        std::string toString(){
            if(this->getBehavior() == MemberElementB_Opertor)
                return "." + this->argment->toString();
            else
            if(this->getBehavior() == MemoryRangeB_Operator)
                return "@";
            else
            if(this->getBehavior() == IndexingB_Operator)
                return "[ " + this->argment->toString() + " ]";
            else
               return "";
        }

    private:

        Token * value       = NULL;
        NodeExpression * argment = NULL;
        ByteOperator * Next = NULL;
        ByteOperator * Prev = NULL;
        ByteOperatorbehavior behavior = Undefined;

    };

    Reference(){}
    Reference(Token * base):Reference(){setBase(base);}
    Reference(Token * value,ByteOperator * byteoperator):Reference(value){setByteOperator(byteoperator);}
    void  setBase(Token *value){this->base = value;}
    void  setReturnType(TypeOfContaint returntype){this->returnType = new TypeOfContaint() ;*this->returnType = returntype;}
    void  setByteOperator(ByteOperator *byteoperator){

        if(this->byteOperator)
        {
            ByteOperator * parcour = this->byteOperator;

            while (parcour->hasNextOperator()) {
                parcour = parcour->getNext();
            }

            parcour->setNext(byteoperator);
            byteoperator->setPrev(parcour);
        }
        else
            this->byteOperator = byteoperator;
    }
    bool  isBaseReference(){return byteOperator == NULL;}
    Token * getBase(){return this->base;}
    TypeOfContaint getReturnType(){return *returnType;}
    ByteOperator *getByteOperator(){return this->byteOperator;}
    std::string toString(){
        std::string res = this->base->Value();
        if(!isBaseReference())
        {
            ByteOperator *bop = this->byteOperator;
            while (bop) {
                res += bop->toString();
                bop  = bop->getNext();
            }
        }
        res += NodeExpression::toString();
        return res;
    }

private:
    Token * base = NULL;
    ByteOperator   *byteOperator = NULL;
    TypeOfContaint *returnType = NULL;
};

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
        if(value->Nature() == KeyWord && (QString::fromStdString(value->Value()).toUpper() == "VRAI" || QString::fromStdString(value->Value()).toUpper() == "FAUX"))
             this->returnType = new TypeOfContaint("BOOLEEN");
        else
        if(value->Value() == "NIL" || value->Value() == "NULLE")
            this->returnType = new TypeOfContaint("NULL"); // CHECK IT
        else
            throw "invalide expression avec le mot '" + value->Value() + "'";
        this->value = value;
        }

    Token*getValue(){return this->value;}
    std::string toString(){
        return value->Value() + NodeExpression::toString();
    }

private:
    Token * value = NULL;

};

class FctCall : public NodeExpression
{
public:
    FctCall(){}
    FctCall(std::string namefct){this->setName(QString::fromStdString(namefct));}
    void AddEffectArg(NodeExpression *arg){listEffctArgs.append(arg);}
    NodeExpression* getEffectArg(int order){listEffctArgs.at(order);}
    bool hasEffectArgs(){return listEffctArgs.size() > 0 ;}
    std::string toString(){
        std::string res = "FN " + this->getName().toStdString() + " (";
        if(this->hasEffectArgs())
        {
            for(int i = 0; i < listEffctArgs.size();i++)
            {
                res += " " + listEffctArgs.at(i)->toString() + " ,";
            }
            res.replace(res.size() - 1 , 1," )");
        }
        else
            res += ")";

        res += NodeExpression::toString();
        return res;
    }

private:
    QList<NodeExpression*> listEffctArgs;
};

class Expression : public NodeExpression
{
public:
    Expression(){}
    Expression(NodeExpression * Node){SetNode(Node);}
    NodeExpression * GetNode(){return this->Node;}
    void SetNode(NodeExpression * Node){this->Node = Node;}
    std::string toString(){
        if(this->Node)
        return  "( " + this->Node->toString() + " )" + NodeExpression::toString() ;
        else
        {
            perror("Expression had not node expression ");
            exit(1);
        }
    }

private:
    NodeExpression * Node = NULL;
};

class ExpressionWithSignelOperator : public NodeExpression{
public:
    ExpressionWithSignelOperator(){}
    ExpressionWithSignelOperator(Token *operatorValue){setOperator(operatorValue);}
    ExpressionWithSignelOperator(NodeExpression * Node,Token *operatorValue){SetNode(Node);setOperator(operatorValue);}
    Token * getOperator(){return operatorValue;}
    NodeExpression * GetNode(){return this->Node;}
    void SetNode(NodeExpression * Node){this->Node = Node;}
    void setOperator(Token * operatorValue){this->operatorValue = operatorValue;}
    std::string toString(){
        return this->getOperator()->Value() + " " + GetNode()->toString();
    }

private:
    NodeExpression * Node = NULL;
    Token * operatorValue;
};

// - ----- EXPRESSIONS
enum StatmentBehavio{
        Debut,ASSIGN,IF,ELSE,FOR,REPEAT,WHILE,CALL_PROCEDURE,WITH
};

class Statment :public ObjectAlgo{
public :
    //explicit Statme
    Statment(){this->childStatments = new QList<Statment*>;}

    Statment(Statment * parent):Statment(){SetParent(parent);parent->addChildStatment(this);}

    Statment(Statment * parent,StatmentBehavio behavior):Statment(parent){SetBehavior(behavior);}

    void addChildStatment(Statment *st){st->SetParent(this); this->childStatments->append(st);}
    void SetParent(Statment * parent){if(parent)this->parent = parent;}
    void SetBehavior(StatmentBehavio behavior){this->behavior = behavior;}
    StatmentBehavio GetBehavior(){return behavior;}
    Statment* GetParent(){return parent;}
    bool virtual hasChildStatments(){return !this->childStatments->isEmpty();}
    QList<Statment*>  getChildStatments(){return *this->childStatments;}
    std::string toString(){
        std::string desc = " ";

        if(this->hasChildStatments())
        {
            for(int i = 0; i < this->childStatments->size();i++)
            {
                desc += this->childStatments->at(i)->toString();
            }
        }

        return desc;
    }
protected:
    Statment * parent = NULL;
    StatmentBehavio behavior;
    QList<Statment*>  * childStatments = NULL;
};

class IF_Statment : public Statment
{
public:
    IF_Statment():Statment(){}

    IF_Statment(Statment * parent):Statment(parent){}

    IF_Statment(NodeExpression *condition){this->setCondition(condition);}

    NodeExpression *getCondition(){return this->condition;}
    void setCondition(NodeExpression *condition){
        this->condition = condition;}
    bool hasElse(){return elseSatment != NULL;}
    void setElseStatment(Statment * elseStatment){this->elseSatment = elseStatment;}
    Statment * getElseStatment(){return this->elseSatment;}
    std::string toString(){
        return "\n SI " + this->condition->toString() + " ALORS \n" + Statment::toString() + "\n FIN SI";
    }
private:
    NodeExpression *condition = NULL;
    Statment * elseSatment = NULL;
};
// Recferance | variable | valeur
class For_Statment : public Statment
{
public:
    For_Statment():Statment(){}

    For_Statment(Statment * parent):Statment(parent){}

    NodeExpression * getVi(){return vi;}
    NodeExpression * getVf(){return vf;}
    NodeExpression * getCompter(){return c;}
    NodeExpression * getStep(){return this->step;}
    bool hasCustomStep(){return this->step != NULL;}
    void setVf(NodeExpression * vf){this->vf = vf;}
    void setVi(NodeExpression * vi){this->vi = vi;}
    void setCompter(NodeExpression * compter){this->c = compter;}
    void setStep(NodeExpression *step){this->step =step;}
    std::string toString(){
        std::string desc = "\n POUR " + this->c->toString() + " DE " + this->vi->toString() + " A " + this->vf->toString() + " ALORS ";
        if(this->hasCustomStep())
            desc += "PAS  = " + this->step->toString() + " \n";
        else
            desc += "\n";
        desc += Statment::toString() + "\n FIN POUR";

        return desc;
    }

private:
    NodeExpression *vi   = NULL;
    NodeExpression *vf   = NULL;
    NodeExpression *c    = NULL;
    NodeExpression *step = NULL;
};

class While_Statment : public Statment
{
public:
    While_Statment():Statment(){}

    While_Statment(Statment * parent):Statment(parent){}

    NodeExpression *getCondition(){return this->condition;}
    void setCondition(NodeExpression * condition){this->condition = condition;}
    std::string toString(){
        return "\n\n TANTE QUE " + this->condition->toString() + " FAIRE \n" + Statment::toString() + "\n FIN TANTE QUE";
    }

private:
    NodeExpression *condition = NULL;
};

class Repeat_Statment : public Statment
{
public:
    Repeat_Statment():Statment(){}

    Repeat_Statment(Statment * parent):Statment(parent){}

    NodeExpression *getCondition(){return this->condition;}
    void setCondition(NodeExpression *condition){this->condition = condition;}
    std::string toString(){
        return "\n REPETER " + Statment::toString() + "\n JUSQU'A " + this->condition->toString();
    }

private:
    NodeExpression *condition;
};

class Case_Statment : public Statment
{
public:
    Case_Statment() {}
    void setCaseValue(Token * value_case){this->value_case = value_case;}
    Token * getCaseValue(){return value_case;}
private:
    Token * value_case;
};

class Swith_Statment : public Statment
{
public:
    Swith_Statment():Statment(){listCases = new QList<Case_Statment*>();}
    Swith_Statment(Statment * parent):Statment(parent){listCases = new QList<Case_Statment*>();}
    void setSelector(NodeExpression * selector){this->selector = selector;}
    void addCaseStatment(Case_Statment * case_stat){if(case_stat)listCases->append(case_stat);}
    NodeExpression * getSelector(){return selector;}
    Case_Statment * getCaseStatment(int index){
        if(index >= listCases->size() || index < 0)
            return NULL;
        else
            return listCases->at(index);
    }
    bool hasElse(){return elseSatment != NULL;}
    void setElseStatment(Statment * elseStatment){this->elseSatment = elseStatment;}
    Statment * getElseStatment(){return this->elseSatment;}

private:
    QList<Case_Statment*> *listCases;
    NodeExpression * selector = NULL;
    Statment * elseSatment = NULL;
};

class CallProc_Statment : public Statment
{
public:
    CallProc_Statment():Statment() {}

    CallProc_Statment(Statment * parent):Statment(parent) {}
};

class Assign_Statment : public Statment
{
public:
    Assign_Statment():Statment() {}

    Assign_Statment(Reference * assign_container):Assign_Statment(){setAssignContainer(assign_container);}

    Assign_Statment(Statment * parent):Statment(parent){}

    void setAssignValue(NodeExpression * value){this->assign_Value = value;}
    void setAssignContainer(Reference * container){this->assign_container = container;}

    NodeExpression * getAssignValue(){return this->assign_Value;}
    Reference * getAssignContainer(){return this->assign_container;}

private:
    NodeExpression * assign_Value;
    Reference  * assign_container;
};

class With_Statment : public Statment{
public:
    With_Statment():Statment(){}
    With_Statment(Statment * parent):Statment(parent){}
    void setSelector(NodeExpression * selector){this->selector = selector;}
    NodeExpression * getSelector(){return this->selector;}
    std::string toString(){
        return "\n AVEC " + selector->toString() + " FAIRE \n" + Statment::toString() + " \n FIN AVEC ";
    }

private:
    NodeExpression * selector = NULL;
};
