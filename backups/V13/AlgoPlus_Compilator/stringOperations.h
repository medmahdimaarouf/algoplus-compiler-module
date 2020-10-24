#include <iostream>
#include<QString>
// + LOCAL FUNCTIONS

#ifndef STRING_OPERATIONS

#include<list>
typedef std::list<std::string> StringList;

int static toInt(std::string pattern){
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

std::string static toUpper(std::string str){
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

std::string static Trim(std::string str){
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

std::string static Number(const int number){
    return QString::number(number).toStdString();
}

bool static isLetter(const char c){
    return c >= 'A' && c<= 'Z' || c >= 'a' && c <= 'z';
}

bool static isDigit(const char c){
    return c >= 0 && c<= 9 ;
}

bool static isSymbol(const char c) {
    return !isLetter(c) && !isDigit(c);
}

bool static count(const char c,const std::string str){
    unsigned int compter = 0;
    for(unsigned int i = 0; i < str.size() && !str.empty();i++)if(str[i] == c)compter++;
    return compter;
}

bool static isLetterOrNumber(const char c){return isLetter(c) || isDigit(c);}

// - LOCAL FUNCTIONS
#endif

#ifndef STRING_OPERATIONS
#define STRING_OPERATIONS "stringOperations.h"
#endif
