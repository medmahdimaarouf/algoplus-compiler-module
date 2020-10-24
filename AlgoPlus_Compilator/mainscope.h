#ifndef MAINSCOPE_H
#define MAINSCOPE_H
#include "function.h"

#ifndef MapProcedures
typedef std::map<StdString,Procedure*> MapProcedures;
#endif

#ifndef MapFunctions
typedef std::map<StdString,Function*> MapFunctions;
#endif

class MainScope : public Scope
{
public:
    MainScope();
    MainScope(StdString name);

    //void  AddSubProgram(Scope &subprogram);
    void  AddFunction(Function &function);
    void  AddProcedure(Procedure &prcoedure);
    Function &getFunction(StdString name);
    Procedure &getProcedure(StdString name);
    bool hasFunction(StdString name);
    bool hasProcedure(StdString name);
    void CheckExistID(StdString id);
    StdString toString();
    void Clear();
private:
    MapProcedures * listProcedures;
    MapFunctions  * listFunctions;


};

#endif // MAINSCOPE_H
