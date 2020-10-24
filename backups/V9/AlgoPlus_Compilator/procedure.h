#ifndef PROCEDURE_H
#define PROCEDURE_H
#include "scope.h"
#include "syntaxicerror.h"

class Procedure  : public Scope{
public:
    Procedure();
    explicit Procedure(Scope &parent);
    Procedure(QString name);
    void setArgs(QMap<QString,Argment> * args);
    QList<Argment> getArgs();
    void addArg(Argment arg);
    bool hasArg(QString argname);
    Argment getArg(QString name);
    void CheckExistID(std::string id);
    std::string toString();
private:
    QMap<QString,Argment>* args;
    QString what = "PROC";
};

#endif // PROCEDURE_H
