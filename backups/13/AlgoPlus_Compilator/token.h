#ifndef TOKEN_H
#define TOKEN_H
#include<iostream>
#include<QString>
#include<QObject>
enum TokenType{
    KeyWord,Punctuation,LogicOperator,LI,RI,Lp,Rp,ArithmeticOperator,NUMBER,ID,STR,CHAR,Reel,AssignValue,AssignType,LocationSpecifier
};

class Token{
public:
    Token();
    Token(const unsigned  int line,const  unsigned  int column);
    Token(const unsigned  int line,const  unsigned  int column,const unsigned  int beginIndex);
    Token(const unsigned  int line, const  unsigned  int column, const unsigned  int beginIndex, Token *backToken);
    Token(TokenType nature,std::string value);
    Token(TokenType nature,std::string value,const  unsigned  int line,const  unsigned  int column);
    TokenType Nature(){return *nature;}
    std::string Value();
    void setValue(std::string value);
    void setNature(TokenType nature);
    void setLine(const unsigned  int line);
    void setColumn( const unsigned int column);
    void setBeginIndex(const unsigned  int beginIndex);
    void setEndIndex(const unsigned  int endIndex);

    int getLineNumber()const;
    int getColumnNumber()const;
    int getBeginIndex()const;
    int getEndIndex()const;

    Token * getNextToken()const;
    Token * getBackToken()const;

    Token * setNextToken(Token *nextToken);
    Token * setBackToken(Token *backToken);
    bool isInLigne()const;
    QString toString();
    std::string stringNature();
private:
    TokenType * nature = NULL;
    std::string value;
    unsigned int line;
    unsigned int column;
    unsigned int beginIndex;
    unsigned int endIndex;
    Token * nextToken = NULL;
    Token * backToken = NULL;
};


#endif // TOKEN_H
