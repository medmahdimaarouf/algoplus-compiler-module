#ifndef TOKEN_H
#define TOKEN_H

#ifndef STDSTRING_H
#include<StdString.h>
#endif


enum TokenType{
    KeyWord,Punctuation,LogicOperator,LI,RI,Lp,Rp,ArithmeticOperator,NUMBER,ID,STR,CHAR,Reel,AssignValue,AssignType,LocationSpecifier
};

class Token{
public:
    Token();
    Token(const unsigned  int line,const  unsigned  int column);
    Token(const unsigned  int line,const  unsigned  int column,const unsigned  int beginIndex);
    Token(const unsigned  int line, const  unsigned  int column, const unsigned  int beginIndex, Token *backToken);
    Token(TokenType nature,StdString value);
    Token(TokenType nature, StdString value, const  unsigned  int line, const  unsigned  int column);
    TokenType Nature(){return *nature;}
    StdString Value();
    void setValue(StdString value);
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
    StdString toString();
    StdString stringNature();
private:
    TokenType * nature = NULL;
    StdString value;
    unsigned int line;
    unsigned int column;
    unsigned int beginIndex;
    unsigned int endIndex;
    Token * nextToken = NULL;
    Token * backToken = NULL;
};


#endif // TOKEN_H
