#include "token.h"

Token::Token()
{

}

Token::Token(const unsigned int line, const unsigned int column)
{
    setLine(line);
    setColumn(column);
}

Token::Token(const unsigned int line, const unsigned int column, const unsigned int beginIndex):Token(line,column)
{
    setBeginIndex(beginIndex);
}


Token::Token(TokenType nature, std::string value)
{
    setNature(nature);this->value = value;
}


Token::Token(TokenType nature, std::string value, const unsigned int line, const unsigned int column)
{
    setNature(nature);this->value = value;setLine(line);setColumn(column);
}

std::string Token::Value()
{
    return value;
}

void Token::setValue(std::string value)
{
    this->value = value;
}

void Token::setNature(TokenType nature)
{
    if(!this->nature)
    {
        this->nature = new TokenType();
        *this->nature =  nature;
    }
}

void Token::setLine(const unsigned int line)
{
    this->line = line;
}

void Token::setColumn(const unsigned int column)
{
    if(column > 1) this->column = column - 1; else this->column = column;
}

void Token::setBeginIndex(const unsigned int beginIndex)
{
    this->beginIndex = beginIndex;
}

void Token::setEndIndex(const unsigned int endIndex)
{
    this->endIndex = endIndex;
}

int Token::getLineNumber() const
{
    return line;
}

int Token::getColumnNumber() const
{
    return column;
}

int Token::getBeginIndex() const
{
    return beginIndex;
}

int Token::getEndIndex() const
{
    return endIndex;
}

Token *Token::getNextToken()
{
    return this->nextToken;
}

Token *Token::getBackToken()
{
    return this->backToken;
}

Token *Token::setNextToken(Token * nextToken)
{
    this->nextToken = nextToken;
}

Token *Token::setBackToken(Token *backToken)
{
    this->backToken = backToken;
}

bool Token::isInLigne() const
{
    if(backToken)return backToken->getLineNumber() == this->getLineNumber();
    else return true;
}

QString Token::toString()
{
    return "Token('" + QString::fromStdString(this->Value()) + "'," + QString::number(this->line) + "," + QString::number(this->column) + ")" ;
}

std::string Token::stringNature()
{
    std::string nature = "Unknown";

    switch (this->Nature()) {

    case Punctuation        :       nature =  "Punctuation";break;
    case LogicOperator      :       nature = "LogicOperator";break;
    case LI                 :       nature = "LI";break;
    case RI                 :       nature = "RI";break;
    case Lp                 :       nature = "Lp";break;
    case Rp                 :       nature = "Rp";break;
    case ArithmeticOperator :       nature = "ArithmeticOperator";break;
    case NUMBER             :       nature = "NUMBER";break;
    case Reel               :       nature = "Reel";break;
    case ID                 :       nature = "ID";break;
    case STR                :       nature = "STR";break;
    case CHAR               :       nature = "CHAR";break;
    case AssignValue        :       nature = "AssignValue";break;
    case AssignType         :       nature = "AssignType";break;
    case LocationSpecifier  :       nature = "LocationSpecifier";break;
    case KeyWord            :       nature = "KeyWord";break;

    }

    return nature;
}
