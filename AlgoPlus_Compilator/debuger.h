#ifndef DEBUGER_H
#define DEBUGER_H
#include<iostream>
#include<stdstring.h>
class Debuger
{
public:

    Debuger();

    Debuger(bool used);

    Debuger operator <<(long l);

    Debuger operator <<(std::string v);

    Debuger operator <<(int v);

    Debuger operator <<(float v);

    Debuger operator <<(double v);

    Debuger operator <<(char v);

    Debuger operator <<(StdString  v);

    Debuger operator <<(const char * v);

    Debuger operator <<(std::ostream f);

    Debuger operator <<(bool b);


    Debuger operator >>(std::string v);

    Debuger operator >>(int v);

    Debuger operator >>(float v);

    Debuger operator >>(double v);

    Debuger operator >>(char v);

    Debuger operator >>(StdString  v);

    Debuger operator >>(const char * v);

    Debuger operator >>(std::ostream f);

    Debuger operator >>(bool b);

    static char endl;
private:
    bool used;
    void __checkSequance(){if(!this->used)std::cout<<std::endl;else this->used = false;}
};

#endif // DEBUGER_H
