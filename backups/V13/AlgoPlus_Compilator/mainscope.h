#ifndef MAINSCOPE_H
#define MAINSCOPE_H
#include "function.h"

#ifndef MapProcedures
typedef std::map<std::string,Procedure*> MapProcedures;
#endif

#ifndef MapFunctions
typedef std::map<std::string,Function*> MapFunctions;
#endif

class MainScope : public Scope
{
public:
    MainScope();
    MainScope(std::string name);

    //void  AddSubProgram(Scope &subprogram);
    void  AddFunction(Function &function);
    void  AddProcedure(Procedure &prcoedure);
    Function &getFunction(std::string name);
    Procedure &getProcedure(std::string name);
    bool hasFunction(std::string name);
    bool hasProcedure(std::string name);
    void CheckExistID(std::string id);
    std::string toString();
    void Clear();
private:
    MapProcedures * listProcedures;
    MapFunctions  * listFunctions;


};

#endif // MAINSCOPE_H
