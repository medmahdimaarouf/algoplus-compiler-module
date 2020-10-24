#ifndef STREAM_H
#define STREAM_H

#include<iostream>
#include<QString>

class Stream : std::string
{
public:

    Stream(){}
    explicit Stream(const basic_string& str):std::string(str){}

    int toInt()
    {
        int res = 0;
        for(int u = 0; u < this->size();u++)
        {
            if((int)this[u] >= '0' && (int)this[u] <= '9' )
                 res = res * 10 + (int)this[u] - 48 ;
            else
                throw "Function ToInt(String pattern):Intrger -> No convertion pattern " + this + " to Integer ";
        }
        return res;
    }

    Stream toUpper()
    {
        std::string res = "";

        for(int i = 0; i < this.size();i++)
        {
            if(this[i] >= 'a' && this[i] <= 'z')
                res += str[i] + 32;
            else
                res += str[i];
        }
        return new Stream(QString::fromStdString(str).toUpper().toStdString());
    }

    Stream trim(){
        while (this.size()) {
            if(this[0] == ' ')
                this.erase(this.begin());
        }
        while (this.size()) {
            if(this[this.size() - 1] == ' ')
                this.erase(this.end());
        }
        return this;
    }

private:

};

#endif // STREAM_H
