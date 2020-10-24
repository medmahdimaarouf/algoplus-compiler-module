#ifndef SYNTAXICANALYSER_H
#define SYNTAXICANALYSER_H


#include "debuger.h"
#include "lexicalanalyser.h"
#include "syntaxicerror.h"
#include "function.h"
#include "compilateur.h"
#include "mainscope.h"
#include <algorithm>


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
#define SINON      "SINON"
#define SI_NON     "SI_NON"
#define Pour       "POUR"
#define Faire      "FAIRE"
#define _A         "A"
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


#include <list>

// ** DELETING **
enum Identificateur_behavior{
    Unknown,id_variable,id_procedure,id_Fucntion,id_argment,id_constante,id_Type
};

typedef struct Identificateur{
    StdString value;
    Identificateur_behavior behavior = Unknown;
    Token token;
}Identificateur;



class SyntaxicAnalyser
{

public:
    explicit SyntaxicAnalyser();
    void AnalyseMainScope(LexicalAnalyser * lex);
    //void Error(CompilationError error);
    NodeExpression* AnalyseExpression(LexicalAnalyser * lex);

private:
     //QDomDocument source;
     void Instructions(Statment *parentstatment, LexicalAnalyser * lex);
     //Expression* AnalyseExpression(LexicalAnalyser * lex);
     Identificateur WhatIs(Token * idToken);

     std::list<StdString> listExOPerators,listByteOpertors,listExSignelOperators,listByteSignelOperators;
     // {"ET","OU","XOU","NON","<",">" ,">=","<=","=","+","-","MOD","DIV","/","*"};

     std::list<StdString> listExtentions;
     void Error(Token * t,StdString desc){if(t)throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),desc);else throw SyntaxicError(1,1,desc);}
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
     bool IN_formalArgs = false;
     bool IN_EffectArgs = false;
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

#endif
