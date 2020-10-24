#ifndef MAINSCOPE_H
#define MAINSCOPE_H
#include "function.h"
class MainScope : public Scope
{
public:
    MainScope();
    MainScope(QString name);

    //void  AddSubProgram(Scope &subprogram);
    void  AddFunction(Function &function);
    void  AddProcedure(Procedure &prcoedure);
    Function &getFunction(QString name);
    Procedure &getProcedure(QString name);
    bool hasFunction(QString name);
    bool hasProcedure(QString name);
    void CheckExistID(std::string id);
    std::string toString();
    void Clear();
private:
    std::map<QString,Procedure*> * listProcedures;
    std::map<QString,Function*>  * listFunctions;


};

#endif // MAINSCOPE_H
