#ifndef TOKEN_H
#define TOKEN_H
#include<iostream>
#include<QString>
enum TokenType{
    KeyWord,Punctuation,LogicOperator,LI,RI,Lp,Rp,ArithmeticOperator,NUMBER,ID,STR,CHAR,Reel,AssignValue,AssignType,LocationSpecifier
};

class Token{
public:
    Token();
    Token(const int line,const int column);
    Token(TokenType nature,std::string value);
    Token(TokenType nature,std::string value,const int line,const int column);
    TokenType Nature(){return *nature;}
    std::string Value();
    void setValue(std::string value);
    void setNature(TokenType nature);
    void setLine(const int line);
    void setColumn(const int column);

    int getLineNumber()const;
    int getColumnNumber()const;
    QString toString();
private:
    TokenType * nature = NULL;
    std::string value;
    int line;
    int column;
};


#endif // TOKEN_H
