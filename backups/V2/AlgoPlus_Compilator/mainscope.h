#ifndef MAINSCOPE_H
#define MAINSCOPE_H
#include "scope.h"
class MainScope : public Scope
{
public:
    MainScope();
    MainScope(QString name);

    void  AddSubProgram(Scope &subprogram);
    Scope &getSubProgram(QString name);
    bool hasSubProgram(QString name){return this->listSubProgrammes->count(name);}
    void CheckExistID(std::string id);
    std::string toString();
    void Clear();
private:
    std::map<QString,Scope*>      * listSubProgrammes;

};

#endif // MAINSCOPE_H
