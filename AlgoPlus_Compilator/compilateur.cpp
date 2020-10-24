#include "compilateur.h"

Compilateur::Compilateur(){
    //liste_motsJS<<"var"<<"function"<<"this"<<"return"<<"String"<<"Object"<<"Array"<<"Date"<<"Math";
    this->ParseTree = new MainScope();
}


void Compilateur::Compiler()
{

}

void Compilateur::Clear()
{
    this->listErrors.clear();
    this->listWarning.clear();

}
