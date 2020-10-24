#include "Char.h"
#define and &&
#define or ||

Char::Char()
{
    data = new char();
}

Char::Char(short code)
{
    data = (char)code;

}

Char::Char(Char::uint code)
{
    data = (char)code;
}

Char::Char(int code)
{
    data = (char)code;
}

Char::Char(char ch)
{
    data = ch;
}

Char::Char(Char::uchar ch)
{
    data = (char)ch;
}

Char::Category Char::category() const
{

}

Char::uint Char::digitValue() const
{
    return (uint)data;
}

bool Char::isDigit() const
{
    return data >= 0 and data <= 9;
}

bool Char::isLetter() const
{
    return data >= 'A' and data <= 'Z' or data >= 'a' and data <= 'z';
}

bool Char::isLetterOrNumber() const
{
    return isLetter() or isNumber();
}

bool Char::isLower() const
{
    return isLetter()?data <= 'z' and data >= 'a':false;
}

bool Char::isNonCharacter() const
{

}

bool Char::isNull() const
{
    return data == NULL;
}

bool Char::isNumber() const
{
    return data >= 0 and data <= 9;
}

bool Char::isPrint() const
{
    return data == '\n' or data == '\t' or data == '\r' or data == '\n' or data == '\1' or data == '\2' or data == '\3';//or data == '\0' can make error
}

bool Char::isPunct() const
{

}

bool Char::isSpace() const
{
    return data == ' ';
}

bool Char::isSymbol() const
{

}

bool Char::isUpper() const
{
    return isLetter()?data <= 'Z' and data >= 'A':false;
}

char Char::toLatin1() const
{
    return data;
}

Char Char::toLower() const
{
    return (char)tolower(data);
}

Char Char::toUpper() const
{
    return (char)toupper(data);
}
