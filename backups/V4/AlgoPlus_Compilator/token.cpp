#include "token.h"

Token::Token()
{

}

Token::Token(const int line, const int column)
{
    setLine(line);
    setColumn(column);
}


Token::Token(TokenType nature, std::string value)
{
    setNature(nature);this->value = value;
}


Token::Token(TokenType nature, std::string value, const int line, const int column)
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

void Token::setLine(const int line)
{
    this->line = line;
}

void Token::setColumn(const int column)
{
    if(column > 1) this->column = column - 1; else this->column = column;
}

int Token::getLineNumber() const
{
    return line;
}

int Token::getColumnNumber() const
{
    return column;
}

QString Token::toString()
{
    return "Token('" + QString::fromStdString(this->Value()) + "'," + QString::number(this->line) + "," + QString::number(this->column) + ")" ;
}
