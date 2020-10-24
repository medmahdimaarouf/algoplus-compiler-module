
#include<headerAlgo.h>

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
    TypeOfContaint getReturnType(){return *returnType;}
    StdString virtual toString(){
        StdString str = StdString("");
        if(this->hasExpressionOperator()){
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
        ByteOperator():ObjectAlgo(StdString("ByteOperator")){}
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
        StdString toString(){
            if(this->getBehavior() == MemberElementB_Opertor)
                return "." + this->argment->toString();
            else
            if(this->getBehavior() == MemoryRangeB_Operator)
                return StdString("@");
            else
            if(this->getBehavior() == IndexingB_Operator)
                return "[ " + this->argment->toString() + " ]";
            else
               return StdString("");
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
    StdString toString(){
        StdString res = this->base->Value();
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
            this->returnType = new TypeOfContaint(StdString("REEL"));
        else
        if(value->Nature() == NUMBER)
            this->returnType = new TypeOfContaint(StdString("ENTIER"));
        else
        if(value->Nature() == STR)
             this->returnType = new TypeOfContaint(StdString("CHAINE"));
        else
        if(value->Nature() == CHAR)
             this->returnType = new TypeOfContaint(StdString("CARACTERE"));
        else
        if(value->Nature() == KeyWord && (value->Value().toUpper() == "VRAI" || value->Value().toUpper() == "FAUX"))
             //this->returnType = new TypeOfContaint("BOOLEEN");
        {ObjectAlgo  *a;
            a->getName();}
        else
        if(value->Value() == "NIL" || value->Value() == "NULLE")
            this->returnType = new TypeOfContaint(StdString("NULL")); // CHECK IT
        else
            throw "invalide expression avec le mot '" + value->Value() + "'";
        this->value = value;
        }

    Token*getValue(){return this->value;}
    StdString toString(){
        return value->Value() + NodeExpression::toString();
    }

private:
    Token * value = NULL;

};
#ifndef ListExpressions
typedef std::list<NodeExpression*> ListExpressions;
#endif
class FctCall : public NodeExpression
{
public:
    FctCall(){}
    FctCall(StdString namefct){this->setName(namefct);}
    void AddEffectArg(NodeExpression *arg){listEffctArgs.push_back(arg);}
    NodeExpression* getEffectArg(int order){return *(listEffctArgs.begin());}//// HHHHHHHHHHHHHHHHHHHHHHHHHERE WE HAVVE ERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRPRRRRRRRRRRRRRRRRRRRRRRRRRRRROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOORRRRRRRRRRRRRRR
    bool hasEffectArgs(){return listEffctArgs.size() > 0 ;}
    StdString toString(){
        StdString res = "FN " + this->getName() + " (";
        if(this->hasEffectArgs())
        {
            for(ListExpressions::iterator i = listEffctArgs.begin(); i != listEffctArgs.end();i++)
            {
                res += " " + (*i)->toString() + " ,";
            }
            //res.replace(res.size() - 1 , 1," )"); HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRREEEEEEEEEE
        }
        else
            res += ")";

        res += NodeExpression::toString();
        return res;
    }

private:
    ListExpressions listEffctArgs;
};

class Expression : public NodeExpression
{
public:
    Expression(){}
    Expression(NodeExpression * Node){SetNode(Node);}
    NodeExpression * GetNode(){return this->Node;}
    void SetNode(NodeExpression * Node){this->Node = Node;}
    StdString toString(){
        if(this->Node)
        return  "( " + this->Node->toString() + " )" + NodeExpression::toString() ;
        else
        {
            perror("erreur d'expression  : aucun noyeu trouvé ");
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
    StdString toString(){
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
    typedef std::list<Statment*> ListStatments;
    Statment(){this->childStatments = new ListStatments;}

    Statment(Statment * parent):Statment(){SetParent(parent);parent->addChildStatment(this);}

    Statment(Statment * parent,StatmentBehavio behavior):Statment(parent){SetBehavior(behavior);}

    void addChildStatment(Statment *st){st->SetParent(this); this->childStatments->push_back(st);}
    void SetParent(Statment * parent){if(parent)this->parent = parent;}
    void SetBehavior(StatmentBehavio behavior){this->behavior = behavior;}
    StatmentBehavio GetBehavior(){return behavior;}
    Statment* GetParent(){return parent;}
    bool virtual hasChildStatments(){return this->childStatments->size();}
    ListStatments  getChildStatments(){return *this->childStatments;}
    StdString toString(){
        StdString desc = StdString(" ");
        if(this->hasChildStatments())for(ListStatments::iterator i = childStatments->begin(); i != childStatments->end();i++)desc += (*i)->toString();
        return desc;
    }
protected:
    Statment * parent = NULL;
    StatmentBehavio behavior;
    ListStatments  * childStatments = NULL;
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
    StdString toString(){
        StdString tostring = "\n SI " + this->condition->toString() + " ALORS \n" + Statment::toString();
        if(hasElse())tostring += "\n     SINON\n" + elseSatment->toString();
        return tostring + "\n FIN SI";
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
    StdString toString(){
        StdString desc = "\n POUR " + this->c->toString() + " DE " + this->vi->toString() + " A " + this->vf->toString() + " ALORS ";
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
    StdString toString(){
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
    StdString toString(){return "\n REPETER " + Statment::toString() + "\n JUSQU'A " + this->condition->toString();}

private:
    NodeExpression *condition;
};

class Case_Statment : public Statment
{
public:
    Case_Statment() {}
    Case_Statment(Statment * parent):Statment(parent) {}
    Case_Statment(Statment * parent,Token*value_case):Statment(parent) {setCaseValue(value_case);}
    void setCaseValue(Token * value_case){if(value_case->Nature() == NUMBER || value_case->Nature() == CHAR)this->value_case = value_case;else throw "Valeur de choix n'est pas de type scalire";}
    Token * getCaseValue(){return value_case;}
    ListStatments * get(){return listToDoStatments;}
    void set(ListStatments * listToDoStatments){this->listToDoStatments = listToDoStatments;}
    void addToDoStatment(Statment * statment){if(!listToDoStatments)listToDoStatments = new ListStatments(); listToDoStatments->push_back(statment);}
    StdString toString(){return "\n " + value_case->Value() + ":" + Statment::toString() + " \n";}

private:
    Token * value_case;
    ListStatments * listToDoStatments = NULL;
};

class Swith_Statment : public Statment
{
public:
    typedef std::list<Case_Statment*> ListCaseStatments;

    Swith_Statment():Statment(){listCases = new ListCaseStatments();}
    Swith_Statment(Statment * parent):Statment(parent){listCases = new ListCaseStatments();}
    void setSelector(NodeExpression * selector){this->selector = selector;}
    void addCaseStatment(Case_Statment * case_stat){if(case_stat)listCases->push_back(case_stat);}
    NodeExpression * getSelector(){return selector;}
    Case_Statment * getCaseStatment(int index = 0){
        ListCaseStatments::iterator iterator = listCases->begin();

        for(int i = 0;iterator != listCases->end();i++,iterator++)if(i == index)return *iterator;

        return NULL;

    }
    bool hasElse(){return elseSatment != NULL;}
    bool hasCaseStatments(){return (listCases)?!listCases->empty():false;}
    void setElseStatment(Statment * elseStatment){this->elseSatment = elseStatment;}
    Statment * getElseStatment(){return this->elseSatment;}

    StdString toString(){
        StdString tostring = "\n SELON (" + selector->toString() + ") FAIRE \n ";
        if(hasCaseStatments()){
            int i = 0;
            for(;i < listCases->size();i++){
                tostring += getCaseStatment(i)->toString();
            }
        }

        if(hasElse())
            tostring += "\n     SINON \n" + elseSatment->toString() + " \n FIN SELON \n";
        return tostring;
    }
    bool hasChildStatments(){
        return hasCaseStatments() || hasElse();
    }

private:
    ListCaseStatments *listCases;
    NodeExpression * selector = NULL;
    Statment * elseSatment = NULL;
};

class CallProc_Statment : public Statment
{
public:
    typedef std::list<NodeExpression*> ListEffectefArgs;

    CallProc_Statment():Statment() {}

    CallProc_Statment(Statment * parent):Statment(parent) {}

    CallProc_Statment(Statment * parent,const StdString idProcedure):Statment(parent) {setIdProcedure(idProcedure);}

    void addEffectifArg(NodeExpression * arg){if(listEffectefArgs == NULL)listEffectefArgs = new ListEffectefArgs;listEffectefArgs->push_back(arg);}

    void setEffectifArgs(ListEffectefArgs * listEffectefArgs){this->listEffectefArgs = listEffectefArgs;}

    ListEffectefArgs * getEffectifArgs(){return listEffectefArgs;}

    bool hasEffectifArgs(){return listEffectefArgs?listEffectefArgs->size():false;}

    StdString getIdProcdure(){return idProcedure;}

    void setIdProcedure(const StdString idProcedure){this->idProcedure = idProcedure;}

    StdString toString(){
        StdString tostring = "\n PROC " + getIdProcdure() + " (";
        if(hasEffectifArgs()){
            ListEffectefArgs::iterator iterator = getEffectifArgs()->begin();

            for(int i = 0; i < getEffectifArgs()->size() - 1;i++,iterator++){
                tostring += (*iterator)->toString() + ",";
            }
            tostring += (*iterator++)->toString() + ")";

        }
        return tostring;
    }

private:
    ListEffectefArgs * listEffectefArgs = NULL;
    StdString idProcedure;
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
    StdString toString(){
        return "\n " + assign_container->toString() + " recoit " + assign_Value->toString() + " \n ";
    }

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
    StdString toString(){
        return "\n AVEC " + selector->toString() + " FAIRE \n" + Statment::toString() + " \n FIN AVEC ";
    }

private:
    NodeExpression * selector = NULL;
};
class ReturnStatment : public Statment{
public:
    ReturnStatment(){}
    ReturnStatment(Statment * parent):Statment(parent){}
    StdString toString(){
        return StdString("\n \n ");
    }
private:
};
