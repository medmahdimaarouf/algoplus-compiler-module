#include "debuger.h"


Debuger::Debuger(bool used)
{
    this->used = used;
}

Debuger::Debuger(){
    used = false;
}

Debuger Debuger::operator <<(long l)
{
    __checkSequance();
    std::cout<<l;
     return Debuger(true);
}

Debuger Debuger::operator <<(std::ostream f)
{
    __checkSequance();
     std::cout<<f;
     return Debuger(true);
}

Debuger Debuger::operator <<(bool b)
{
    __checkSequance();
    std::cout<<b;
     return Debuger(true);
}

Debuger Debuger::operator<<(char v){
    __checkSequance();
    std::cout<<v;
     return Debuger(true);
}

Debuger Debuger::operator<<(double v){
    __checkSequance();
    std::cout<<v;
     return Debuger(true);
}

Debuger Debuger::operator<<(float v){
     __checkSequance();
    std::cout<<v;
     return Debuger(true);
}

Debuger Debuger::operator<<(int v){
     __checkSequance();
     std::cout<<v;
     return Debuger(true);
}

Debuger Debuger::operator<<(std::string v){
     __checkSequance();
    std::cout<<v;
     return Debuger(true);
}

Debuger Debuger::operator<<(StdString v){
     __checkSequance();
    std::cout<<v.toStdString();
     return Debuger(true);
}

Debuger Debuger::operator<<(const char *v)
{
     __checkSequance();
    for(int i = 0; i < strlen(v);i++)std::cout<<*(v+i);
     return Debuger(true);
}

Debuger Debuger::operator>>(std::string v){

    std::cout<<v<<std::endl;
     return Debuger(true);
}

Debuger Debuger::operator>>(int v){
    std::cout<<v<<std::endl;
     return Debuger(true);
}

Debuger Debuger::operator>>(float v){
    std::cout<<v<<std::endl;
     return Debuger(true);
}

Debuger Debuger::operator>>(double v){
    std::cout<<v<<std::endl;
     return Debuger(true);
}

Debuger Debuger::operator>>(char v){
    std::cout<<v<<std::endl;
     return Debuger(true);
}

Debuger Debuger::operator>>(StdString  v){
    std::cout<<v.toStdString();
     return Debuger(true);
}

Debuger Debuger::operator>>(const char * v){
    for(int i = 0; i < strlen(v);i++)std::cout<<*(v+i);
    std::cout<<v<<std::endl;
     return Debuger(true);
}

Debuger Debuger::operator>>(std::ostream f){
    std::cout<<f<<std::endl;
     return Debuger(true);
}

Debuger Debuger::operator >>(bool b)
{
    std::cout<<b<<std::endl;
    return Debuger(true);
}


