#ifndef PROCEDURE_H
#define PROCEDURE_H
#include "scope.h"
#include "syntaxicerror.h"
typedef std::map<std::string,Argment>   MapArgs;
typedef std::list<Argment>          ListArgs;
class Procedure  : public Scope{
public:
    Procedure();
    explicit Procedure(Scope &parent);
    Procedure(std::string name);
    void setArgs(MapArgs * args);
    ListArgs getArgs();
    void addArg(Argment arg);
    bool hasArg(std::string argname);
    Argment getArg(std::string name);
    void CheckExistID(std::string id);
    std::string toString();
private:
    MapArgs * args;
    std::string what = "PROC";
};

#endif // PROCEDURE_H
