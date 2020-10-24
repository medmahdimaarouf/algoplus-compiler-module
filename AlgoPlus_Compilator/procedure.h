#ifndef PROCEDURE_H
#define PROCEDURE_H
#include "scope.h"
#include "syntaxicerror.h"
typedef std::map<StdString,Argment>   MapArgs;
typedef std::list<Argment>          ListArgs;
class Procedure  : public Scope{
public:
    Procedure();
    explicit Procedure(Scope &parent);
    Procedure(StdString name);
    void setArgs(MapArgs * args);
    ListArgs getArgs();
    void addArg(Argment arg);
    bool hasArg(StdString argname);
    Argment getArg(StdString name);
    void CheckExistID(StdString id);
    StdString toString();
private:
    MapArgs * args;
    StdString what = StdString("PROC");
};

#endif // PROCEDURE_H
