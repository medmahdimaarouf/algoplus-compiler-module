#include <iostream>
#include<QString>
// + LOCAL FUNCTIONS

int toInt(std::string pattern)
{
    int res = 0;
    for(int u = 0; u < pattern.size();u++)
    {
        if((int)pattern[u] >= '0' && (int)pattern[u] <= '9' )
             res = res * 10 + (int)pattern[u] - 48 ;
        else
            throw "Function ToInt(String pattern):Intrger -> No convertion pattern " + pattern + " to Integer ";
    }
    return res;
}

std::string toUpper(std::string str)
{
    /*std::string res = "";
    for(int i = 0; i < str.size();i++)
    {
        if(str[i] >= 'a' && str[i] <= 'z')
            res += str[i] + 32;
        else
            res += str[i];
    }*/
    return  QString::fromStdString(str).toUpper().toStdString();
}

std::string Trim(std::string str)
{
    while (str.size()) {
        if(str[0] == ' ')
            str.erase(str.begin());
    }
    while (str.size()) {
        if(str[str.size() - 1] == ' ')
            str.erase(str.end());
    }
    return str;
}


// - LOCAL FUNCTIONS
