#ifndef LEXICALANALYSER_H
#define LEXICALANALYSER_H


/// ** WORDS MUST BE AS REGULAR KEYWORD
///    "ALGORITHME","FN","NIL","NULL","NULLE"...
///***
// -- Arithmetic Symbols
#define Addition_char    '+'
#define Subtraction_char '-'
#define Modulo_char      '%'
#define Multip_char      '*'
#define Division_char    '/'
// -- Comparison Symbols
#define Less_char        '<'
#define Gran_char        '>'
#define Egal_char        '='
// -- Punctuation Symbols
#define Comma_char       ','
#define Semicolon_char   ';'
#define Dot_char         '.'
#define Arrow_char       '@'
#define LP_char          '('
#define Rp_char          ')'
#define LI_char          '['
#define RI_char          ']'
#define Comment_char     '#'
#define Under_s_char     '_'
#define Space_char       ' '
#define tab_char         '\t'
#define Endl_char        '\n'
// --
#include "lexicalerror.h"
#include <token.h>

#ifndef ListTokens
typedef std::list<Token*> ListTokens;
#endif

class LexicalAnalyser
{

public:
    explicit LexicalAnalyser();

    void StartAnalyse();
    std::string setStream(const std::string stream) ;
    Token * NextToken();
    Token * BackToken();
    Token * SeekToken(Token *token);
    bool static isIdToken(const std::string token) ;
    int currentLine(){return this->Currentlignecode;}
    int currentColumn(){return this->CurrentColumnlignecode;}
    Token * lookAhead();

    Token * getCurrentToken() const;

    Token *getLastToken() const;

private:
    Token * currentToken = NULL;
    Token * lastToken = NULL;

    void Advance();
    void deleteBlanks();
    void IngioreComment();
    std::string Number(bool *reel);
    std::string Id() ;
    std::string str();
    std::string chr();
    std::string Advance(const int nbc);
    std::string lookAhead(const int nbc) const;

    std::string stream;

    ListTokens listTokns;
    int currentIndex = 0;
    int unsigned static Currentlignecode;
    int unsigned static CurrentColumnlignecode;
};
// METHODE THROWS LEXICAL ERROR
#endif // LEXICALANALYSER_H
