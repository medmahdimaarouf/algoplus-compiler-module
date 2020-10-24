#ifndef LEXICALANALYSER_H
#define LEXICALANALYSER_H

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
//char  mc[][20]= {"ALGORITHME","DEBUT","FIN","SI","ALORS","TANTE_QUE","FAIRE","VARIABLES","TABLEAU","ENTIER","DE","ET","NON","OU","POUR"};
//char  cs[][20]= {"=","<>","<",">","<=",">=","+","-","/","*","..",".",":","(",")",",",";","[","]","{","}","'"};
//char  op[][20]= {"=","<",">",">","+","-","/","*",".",":","(",")",",",";","[","]","'"};
// --
#include <QObject>
#include <QtCore>
#include "lexicalerror.h"
#include<token.h>

class LexicalAnalyser
{

public:
    explicit LexicalAnalyser();

    //void StartXMLAnalyse(QDomDocument xmlPattern);
    void StartAnalyse();
    void setStream(QString stream);
    Token * NextToken();
    Token * BackToken();
    Token * SeekToken( Token *token);
    QStringList toListTokens(QString expression);
    bool static isIdToken(QString token);
    int currentLine(){return this->Currentlignecode;}
    int currentColumn(){return this->CurrentColumnlignecode;}
    Token * currentToken = NULL;
    Token * lastToken = NULL;
    Token * lookAhead();
private:
    void Advance();
    void deleteBlanks();
    void IngioreComment();
    std::string Number(bool *reel);
    std::string Id();
    std::string str();
    std::string chr();
    std::string Advance(const int nbc);
    std::string lookAhead(const int nbc);
    TokenType NatureFromId(std::string id);
    QString stream;
    QStringList listTokns;

    int currentIndex = 0;
    int static Currentlignecode;
    int static CurrentColumnlignecode;
    //char static * keyWords[];
};
// METHODE THROWS LEXICAL ERROR
#endif // LEXICALANALYSER_H
