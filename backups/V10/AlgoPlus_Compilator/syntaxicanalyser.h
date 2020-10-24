#ifndef SYNTAXICANALYSER_H
#define SYNTAXICANALYSER_H

#include "lexicalanalyser.h"
#include "syntaxicerror.h"
#include "function.h"
#include<compilateur.h>
#include<mainscope.h>

#include <list>
#include <QtXml>
/* delete this */
/* I mean ^| */
#define Algorithme "ALGORITHME"
#define Extention  "EXTENTION"
#define Constantes "CONSTANTES"
#define Types      "TYPES"
#define Variables  "VARIABLES"
#define Debut      "DEBUT"
#define FIN        "FIN"
#define Enregistrement "ENREGISTREMENT"
#define Tableau    "TABLEAU"
#define Ficheir    "FICHIER"
#define Fonction   "FONCTION"
#define PRocedure  "PROCEDURE"
//#define Text       "TEXT"

#define Si         "SI"
#define Alors      "ALORS"
#define Pour       "POUR"
#define Faire      "FAIRE"
#define A          "A"
#define Repeter    "REPETER"
#define Jusqu_A    "JUSQU_A"
#define TanteQue   "TANTEQUE"
#define Selon      "SELON"
#define NON        "NON"
#define Pas        "PAS"
#define Avec       "AVEC"
#define FN         "FN"
#define VRAI       "VRAI"
#define FAUX       "FAUX"
#define Retourner  "RETOURNER"
// ** DELETING **
enum Identificateur_behavior{
    id_variable,id_procedure,id_Fucntion,id_argment,id_constante,id_Type
};

typedef struct Identificateur{
    std::string value;
    Identificateur_behavior behavior;
    Token token;
}Identificateur;

class SyntaxicAnalyser : public QObject
{
    Q_OBJECT
public:
    explicit SyntaxicAnalyser(QObject *parent = 0);
    // + XML
    void XMLAnalyse(QDomDocument source);
    void XMLAnalyse();
    void ScaneXMLStatment(QDomElement xmlStatment, Statment *statment, int *ligne);
    void ScaneHeaderXMLScope(QDomElement rootHeader,Scope * scope, int *ligne);
    void ScaneCoreXMLScope(QDomElement root, Scope * scope, int *ligne);
    // - XML
    void AnalyseMainScope(LexicalAnalyser * lex);
    //void Error(CompilationError error);
    NodeExpression* AnalyseExpression(LexicalAnalyser * lex);

    Token * endToken = NULL;

signals:
    void Handle_Error(const int ligne,SyntaxicError e);
    void Handle_Warning(const int ligne,QString w);

private:
     QDomDocument source;
     void Instructions(Statment *parentstatment, LexicalAnalyser * lex);
     //Expression* AnalyseExpression(LexicalAnalyser * lex);
     Identificateur checkBehaviorID(Token * token);

     QList<std::string> listExOPerators,listByteOpertors,listExSignelOperators,listByteSignelOperators;
     // {"ET","OU","NON","<",">" ,">=","<=","=","+","-","MOD","DIV","/","*"};

     QList<std::string> listExtentions;
     void Error(Token * t,std::string desc){throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),desc);}
     Scope * currentScope ;

     bool IN_Id_Algo    = true;
     bool IN_Algorithme = true;
     bool IN_id_program = false;

     bool IN_HeaderProgram = false;

    // Extentions
     bool IN_Directives = false;
     bool IN_Extention  = false;
     bool IN_FileName   = false;
    // Constantes
     bool IN_Constantes = false;
     bool IN_ListConsts = false;
     bool IN_Const      = false;
     bool IN_IDConst    = false;
     bool IN_OperatorConst= false;
     bool IN_ConstValue = false;
    // Types
     bool IN_Types      = false;
     bool IN_Listtypes  = false;
     bool IN_Type       = false;
     bool IN_Id_Type    = false;
     bool IN_OpertatorType=false;
     bool IN_ContaintType=false;
     bool IN_DefType    = false;
        // tab / Mat
     bool IN_Tab        = false;
     bool IN_Mat        = false;
     bool IN_InitSizeT  = false;
     bool IN_size_c     = false;
     bool IN_size_l     = false;
     bool IN_DE_Key     = false;
        // Record
     bool IN_Enreg      = false;
     bool IN_listFields = false;
     bool IN_ID_Field   = false;
     bool IN_typeOfField= false;
        // File
     bool IN_Fich       = false;
        // Qalifier
     bool IN_Qalifier   = false;
    // Variables
     bool IN_Variables  = false;
     bool IN_listVars   = false;
     bool IN_Id_Var     = false;
     bool IN_TypeOfVar  = false;
    // Sub_Programmes
     bool IN_Fct        = false;
     bool IN_id_fct     = false;
     bool IN_Proc       = false;
     bool IN_IdProc     = false;
     bool IN_listArgs   = false;
     bool IN_returnType = false;
     bool IN_ES         = false;
     bool IN_IdArg      = false;
     bool IN_typeOfArg  = false;
     bool IN_Debut      = false;
     int size_c = 0;
     bool IN_End        = false;
     bool require       = false;
     bool IN_LI = false, IN_RI  = false ,IN_Lp = false,IN_Rp = false,IN_STR = false,IN_CHR = false,IN_Reel = false,IN_AssignValue = false,IN_AssignType = false,IN_LocationSpecifier = false,IN_Punctiation = false;

     bool signe = false;

};

#endif // SYNTAXICANALYSER_H
