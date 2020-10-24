#ifndef CHAR_H
#define CHAR_H
#include<iostream>

class Char
{
public:
    typedef unsigned char uchar;
    typedef unsigned short ushort;
    typedef unsigned int uint;
    typedef unsigned long ulong;
    enum Category{

        Mark_NonSpacing,          //   Mn
        Mark_SpacingCombining,    //   Mc
        Mark_Enclosing,           //   Me

        Number_DecimalDigit,      //   Nd
        Number_Letter,            //   Nl
        Number_Other,             //   No

        Separator_Space,          //   Zs
        Separator_Line,           //   Zl
        Separator_Paragraph,      //   Zp

        Other_Control,            //   Cc
        Other_Format,             //   Cf
        Other_Surrogate,          //   Cs
        Other_PrivateUse,         //   Co
        Other_NotAssigned,        //   Cn

        Letter_Uppercase,         //   Lu
        Letter_Lowercase,         //   Ll
        Letter_Titlecase,         //   Lt
        Letter_Modifier,          //   Lm
        Letter_Other,             //   Lo

        Punctuation_Connector,    //   Pc
        Punctuation_Dash,         //   Pd
        Punctuation_Open,         //   Ps
        Punctuation_Close,        //   Pe
        Punctuation_InitialQuote, //   Pi
        Punctuation_FinalQuote,   //   Pf
        Punctuation_Other,        //   Po

        Symbol_Math,              //   Sm
        Symbol_Currency,          //   Sc
        Symbol_Modifier,          //   Sk
        Symbol_Other              //   So
    };

    Char();
    Char(short code);
    Char(uint code);
    Char(int code);
    Char(char ch);
    Char(uchar ch);
    Category category() const;
    uint digitValue() const;
    bool isDigit() const;
    bool isLetter() const;
    bool isLetterOrNumber() const;
    bool isLower() const;
    bool isNonCharacter() const;
    bool isNull() const;
    bool isNumber() const;
    bool isPrint() const;
    bool isPunct() const;
    bool isSpace() const;
    bool isSymbol() const;
    bool isUpper() const;
    char toLatin1() const;
    Char toLower() const;
    Char toUpper() const;
    /* NOT READY YET
    ushort unicode() const;
    ushort &unicode();
    */
private:
    char * data = NULL;
};

#endif // CHAR_H
