#include "syntaxicanalyser.h"

// + LOCAL INSTANCES
    Constant    *c   = NULL;
    Function    *f   = NULL;
    Procedure   *p   = NULL;
    RecordType *RDT  = NULL;
    Array      *array= NULL;
    MatrixType *mat  = NULL;
    FileType   *file = NULL;
    QalifierType*QAT = NULL;
    Argment * arg;
// - LOCAL INSTANCES

// + LOCAL KITS
    std::string id_type = "",containttype = "";
    std::string id_var = "",typeVar = "";
    std::string id_Field = "",typeField = "";
    std::string id_program = "",returntype = "";
    std::string id_compteur = "",vi_pour = "",vf_pour = "";
    int unsigned memoryRange = 0;
// - LOCAL KITS

// + LOCAL COLLECTIONS
    //std::list<std::string> listVirtualID;
    QList<std::string> listVirtualID;
// - LOCAL COLLECTIONS

// + STATIC FIELDS
    MainScope *Compilateur::ParseTree = new MainScope();
// - STATIC FIELDS

// + LOCAL FUNCTIONS
    int toInt(std::string pattern)
    {
        int res = 0;
        for(int u = 0; u < pattern.size();u++)
        {
            if((int)pattern[u] >= '0' && (int)pattern[u] <= '9' )
                 res = res * 10 + (int)pattern[u] - 48 ;
            else
                throw "Function ToInt(std::string pattern):int -> No convertion pattern " + pattern + " to int ";
        }
        return res;
    }

    std::string toUpper(std::string str)
    {
        return QString::fromStdString(str).toUpper().toStdString();
    }
// + LOCAL FUNCTIONS

SyntaxicAnalyser::SyntaxicAnalyser(QObject *parent) :
    QObject(parent)
{
    //this->currentScope = new MainScope();
    AnalyseMemory = new QList<Token*>();
    listExOPerators<< "ET"<<"OU"<<"NON"<<"<"<<">" <<">="<<"<="<<"="<<"+"<<"-"<<"MOD"<<"DIV"<<"/"<<"*";
    listByteOpertors<<"."<<"["<<"@";
    //this->currentScope = Compilateur::ParseTree;
}

void SyntaxicAnalyser::AnalyseMainScope(LexicalAnalyser *lex)
{
    Token * t = lex->NextToken();
    while (t) {
        ReloadAll:{

            if(IN_Id_Algo)
            {
                if(IN_Algorithme)
                {
                    Algorithme_:{
                        if(toUpper(t->Value()) != Algorithme)
                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle 'Algorithme' Attendu mais le mot '" + t->Value() + "' trouve " );
                        else
                        {
                            IN_Algorithme = false;
                            IN_id_program = true;
                        }
                    }
                }
                else
                 {
                      if(t->Nature() == ID)
                      {
                          Compilateur::ParseTree->setName(QString::fromStdString(t->Value()).toUpper());
                          IN_id_program = false;
                          IN_Id_Algo    = false;
                          IN_Directives = true;
                          IN_Extention  = true;

                      }
                      else
                      if(t->Nature() == KeyWord )
                          throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"'" + t->Value() + "' est un mot reserve algorithmique ");
                      else
                         throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Identifateur du programme incorrecte " );
                  }
            }
            else
            if(IN_Directives)
            {
                if(IN_Extention)
                {
                    if(toUpper(t->Value()) != Extention)
                    {
                        IN_Directives = false;
                        IN_HeaderProgram = true;
                        goto ReloadAll;
                    }
                    else
                    {
                        IN_Extention = false;
                        IN_FileName = true;
                    }
                }
                else
                {
                    if(t->Nature() != STR)
                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber()," invalide nom du fichier d'extention ");
                    else
                    {
                        // TRaitement include ( t->Value());
                        listExtentions << t->Value();
                        IN_FileName = false;
                        IN_Extention = true;
                    }
                }
            }
            else
            if(IN_HeaderProgram)
            {
                    //qDebug()<< "ici "<<QString::fromStdString(t->Value())<< IN_Constantes << IN_Types << IN_Variables << IN_Fct << IN_Proc;

                    if(IN_Constantes == false && IN_Types == false && IN_Variables == false)
                    {

                        if(t->Nature() != ID)
                        {
                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"indication ambigue par le mot suivant : " + t->Value());
                        }
                        else
                            if(toUpper(t->Value()) == Constantes)
                            {
                                IN_Constantes = true;
                                IN_ListConsts = true;
                                IN_listVars = IN_Listtypes = false;
                                IN_IDConst = true;
                            }
                        else
                            if(toUpper(t->Value()) == Types)
                            {
                                IN_Listtypes=true;
                                IN_Types = true;
                                IN_listVars = IN_ListConsts = false;
                                IN_Id_Type = true;
                            }
                        else
                            if(toUpper(t->Value()) == Variables)
                            {
                                IN_Types = false;
                                IN_Variables = true;
                                IN_Id_Var = true;
                                IN_ListConsts = IN_Listtypes = false;
                                IN_listVars = true;
                            }
                        else
                            if(toUpper(t->Value()) == Fonction)
                            {
                                if(IN_Proc || IN_Fct)
                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Declaration imprique des sous programmes interdit ");
                                else
                                {
                                    IN_ListConsts = IN_Listtypes = IN_listVars = false;
                                    IN_HeaderProgram = false;
                                    IN_Fct = true;
                                    IN_id_fct = true;
                                    f = new Function(*Compilateur::ParseTree);
                                }
                            }
                        else
                             if(toUpper(t->Value()) == PRocedure)
                            {
                                 if(IN_Proc || IN_Fct)
                                     throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Declaration imprique des sous programmes interdit ");
                                 else
                                 {
                                     IN_ListConsts = IN_Listtypes = IN_listVars = false;
                                     IN_HeaderProgram = false;
                                     IN_Proc   = true;
                                     IN_IdProc = true;
                                     p = new Procedure(*Compilateur::ParseTree);
                                 }

                            }
                        else
                            if(toUpper(t->Value()) == Debut)
                            {
                                 IN_ListConsts = IN_Listtypes = IN_listVars = false;
                                 IN_HeaderProgram = false; // FERMER LE HEADER DU PROGRAMME PUIS ALLER VERS LE DEBUT
                                 IN_Debut = true;
                                 goto ReloadAll;
                                 //qDebug()<< "tets : IN fuction Deb : " << IN_Fct << " IN proc deb : " << IN_Proc;
                            }
                        else
                            {
                                if(IN_ListConsts)
                                {
                                    IN_Constantes = true;
                                    goto ID_Const;
                                }
                                else
                                if(IN_Listtypes)
                                {
                                    IN_Types = true;
                                    IN_Id_Type = true;
                                    goto Type;
                                }
                                else
                                if(IN_listVars)
                                {
                                    IN_Variables = true;
                                    IN_Id_Var = true;
                                    goto Var;
                                }
                                else
                                {
                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"indication ambigue par le mot suivant : " + t->Value());
                                }
                            }
                    }
                    else
                    if(IN_Constantes)
                    {
                            IN_ListConsts = true;
                            if(IN_IDConst)
                            {
                                ID_Const:{
                                    if(t->Nature() != ID)
                                    {
                                        if(t->Nature() == KeyWord)
                                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"'" + t->Value() + "' est un mot reserve algorithmique ");
                                        else
                                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"identificateur du contante incorrecte");
                                    }
                                    else
                                    {
                                        c = new Constant(QString::fromStdString( t->Value()).toUpper());
                                        IN_IDConst = false;
                                        IN_OperatorConst = true;
                                    }
                                }
                            }
                            else
                            if(IN_OperatorConst)
                            {
                                OperatorConst:{
                                if(t->Value() != "=")
                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Erreur du synatax '=' attendu  ");
                                else
                                {
                                    IN_OperatorConst = false;
                                    IN_ConstValue = true;
                                 }
                            }
                            }else
                            {
                                ConstValue:{
                                        if(t->Value() == "-" && t->Nature() == ArithmeticOperator && !signe)
                                           {
                                               signe = true;
                                           }
                                        else
                                        if(t->Nature() == NUMBER || t->Nature() == Reel || t->Nature() == STR || t->Nature() == CHAR)
                                        {
                                            if(signe && (t->Nature() == STR || t->Nature() == CHAR))
                                                throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Signe incompatible avec le type du valeur ");
                                            else
                                            {
                                                if(signe)
                                                    c->setValue(QString::fromStdString("-" + t->Value()));
                                                else
                                                    c->setValue(QString::fromStdString(t->Value()));
                                                try
                                                {
                                                    if(f)
                                                        f->AddConstant(*c);
                                                    else
                                                    if(p)
                                                        p->AddConstant(*c);
                                                    else
                                                        Compilateur::ParseTree->AddConstant(*c);
                                                    //this->currentScope->AddConstant(*c);

                                                }catch(std::string error)
                                                {
                                                    throw SyntaxicError(t->getLineNumber(),0,error);
                                                }

                                                c = NULL;
                                                signe = false;
                                                IN_ConstValue = false;
                                                IN_Constantes = false;
                                            }

                                        }
                                        else
                                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Valuer du constantes incorrecte ");
                                    }

                            }
                    }
                    else
                    if(IN_Types)
                    {
                        //qDebug()<< "in types: "<<QString::fromStdString(t->Value());
                        Type:{
                                IN_Listtypes = true;

                                if(IN_Id_Type)
                                {
                                    if(t->Nature() == ID)
                                    {
                                        id_type = toUpper( t->Value());
                                        IN_Id_Type = false;
                                        IN_OpertatorType = true;
                                    }
                                    else
                                    {
                                        if(t->Nature() == KeyWord)
                                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"'" + t->Value() + "' est un mot reserve algorithmique ");
                                        else
                                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"identificateur du type invalide ");
                                    }
                                }
                                else
                                if(IN_OpertatorType)
                                {
                                    if(t->Value() == "=")
                                    {
                                        IN_OpertatorType = false;
                                        IN_DefType = true;
                                    }
                                    else
                                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle '=' de deffinition du type est attendu");
                                }
                                else
                                {
                                    if(!IN_Enreg && !IN_Tab && !IN_Mat && !IN_Fich && !IN_Qalifier)
                                      {
                                          if(t->Nature() != ID)
                                          {
                                              if(t->Nature() == KeyWord)
                                                  throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"'" + t->Value() + "' est un mot reserve algorithmique ");
                                              else
                                              if(t->Nature() == LocationSpecifier)
                                              {
                                                  IN_DefType = true;
                                                  IN_Qalifier = true;
                                                  QAT = new QalifierType(QString::fromStdString(id_type).toUpper());
                                                  try
                                                  {
                                                      if(f)
                                                          f->AddType(QAT);
                                                      else
                                                      if(p)
                                                          p->AddType(QAT);
                                                      else
                                                          Compilateur::ParseTree->AddType(QAT);
                                                  }catch(std::string error)
                                                  {
                                                      throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),error);
                                                  }

                                                  goto Type;
                                              }
                                              else
                                                  throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Indicateur du type incorrecte");
                                          }
                                          else
                                          if(toUpper(t->Value()) == Enregistrement)
                                          {
                                                IN_DefType = false;
                                                IN_Enreg = true;
                                                IN_ID_Field = true;
                                                IN_listFields = true;
                                                RDT = new RecordType();
                                                RDT->setName(QString::fromStdString(id_type).toUpper());
                                                try{
                                                    if(f)
                                                        f->AddType(RDT);
                                                    else
                                                        if(p)
                                                            p->AddType(RDT);
                                                        else
                                                            Compilateur::ParseTree->AddType(RDT);
                                                }catch(std::string error)
                                                {
                                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),error);
                                                }


                                          }
                                          else
                                          if(toUpper(t->Value()) == Tableau)
                                          {
                                                IN_DefType = false;
                                                IN_Tab = true;
                                                IN_LI = true;
                                          }
                                          else
                                          if(toUpper(t->Value()) == Ficheir)
                                          {
                                                IN_DefType = false;
                                                IN_Fich = true;
                                                IN_DE_Key = true;
                                                file = new FileType(QString::fromStdString(id_type).toUpper());
                                                try{
                                                    if(f)
                                                        f->AddType(file);
                                                    else
                                                        if(p)
                                                            p->AddType(file);
                                                        else
                                                            Compilateur::ParseTree->AddType(file);
                                                }catch(std::string error)
                                                {
                                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),error);
                                                }


                                          }
                                          else
                                          if(t->Nature() == LocationSpecifier || t->Nature() == ID)
                                          {
                                                IN_DefType = true;
                                                IN_Qalifier = true;
                                                QAT = new QalifierType(QString::fromStdString(id_type).toUpper());
                                                try
                                                {
                                                    if(f)
                                                        f->AddType(QAT);
                                                    else
                                                    if(p)
                                                        p->AddType(QAT);
                                                    else
                                                        Compilateur::ParseTree->AddType(QAT);
                                                }catch(std::string error)
                                                {
                                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),error);
                                                }

                                                goto Type;
                                          }
                                          else
                                              throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Deffinition du type illegale '" + t->Value() + "'");

                                    }
                                    else
                                      {
                                            if(IN_Enreg)
                                            {
                                                Enreg:{
                                                    if(IN_listFields)
                                                    {
                                                        if(IN_ID_Field)
                                                        {
                                                            if(t->Nature() == ID)
                                                            {

                                                                id_Field = toUpper(t->Value());
                                                                IN_ID_Field = false;
                                                                IN_AssignType = true;

                                                            }
                                                            else
                                                            {
                                                                if(t->Nature() == KeyWord)
                                                                {
                                                                    if(toUpper(t->Value()) == FIN)
                                                                    {
                                                                        IN_listFields = false;
                                                                        IN_End = true;
                                                                    }
                                                                    else
                                                                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"'" + t->Value() + "' est un mot reserve algorithmique ");
                                                                }
                                                                else
                                                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"identificateur du champ incorrecte ");
                                                            }
                                                        }
                                                        else
                                                        if(IN_AssignType)
                                                        {
                                                            if(t->Nature() == AssignType)
                                                            {
                                                                IN_AssignType = false;
                                                                IN_typeOfField = true;
                                                            }
                                                            else
                                                                throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"mot cle ':' de attendu ");
                                                        }
                                                        else
                                                        {
                                                            if(t->Nature() == LocationSpecifier)
                                                                memoryRange++;
                                                            else
                                                                if(t->Nature() == ID)
                                                                {

                                                                    try{
                                                                        FieldRecord field ;
                                                                        field.nom  = QString::fromStdString(id_Field).toUpper();

                                                                         if(f)
                                                                             field.type = f->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                                                         else
                                                                         if(p)
                                                                             field.type = p->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                                                         else
                                                                             field.type = Compilateur::ParseTree->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                                                        field.type.addMemoryRange(memoryRange);
                                                                        memoryRange = 0;
                                                                        RDT->AddField(field);

                                                                        id_Field = typeField = "";
                                                                        IN_ID_Field = true;
                                                                    }catch(std::string error)
                                                                    {
                                                                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),error);
                                                                    }
                                                                    IN_typeOfField = false;
                                                                }
                                                                else
                                                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Type du champ incorrecte ");

                                                        }
                                                    }
                                                    else // IN END RECORD
                                                    {
                                                        IN_End  = false;
                                                        IN_Enreg = false;
                                                        IN_Types = false;
                                                        IN_DefType = false;

                                                        /*if(f)
                                                            f->AddType(*RDT);
                                                        else
                                                        if(p)
                                                            p->AddType(*RDT);
                                                        else
                                                            Compilateur::ParseTree->AddType(*RDT);
                                                        */
                                                        if(toUpper(t->Value()) != toUpper(id_type) && toUpper(t->Value()) != Enregistrement)
                                                            goto ReloadAll;
                                                    }
                                                }
                                            }
                                            else
                                            if(IN_Tab)
                                            {
                                                Tab:{
                                                        //qDebug()<< "test IN Tab : " << QString::fromStdString(t->Value())<<IN_LI<<IN_InitSizeT<< IN_Punctiation<<IN_size_c<<IN_RI<<IN_DE_Key<<IN_ContaintType<<"\n";
                                                        if(IN_LI)
                                                        {

                                                             if(t->Nature() == LI)
                                                             {
                                                                 IN_LI = false;
                                                                 IN_InitSizeT = true;
                                                             }
                                                             else
                                                                 throw SyntaxicError(t->getLineNumber(),t->getColumnNumber()," Mot cle '[' attendu ");

                                                        }
                                                        else
                                                        if(IN_InitSizeT)
                                                        {
                                                            if(t->Nature() == NUMBER)
                                                            {
                                                                IN_InitSizeT = false;
                                                                IN_Punctiation = true;
                                                            }else
                                                                throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Borne inferieur du tableux attendu ");
                                                        }
                                                        else
                                                        if(IN_Punctiation)
                                                        {
                                                            if(t->Nature() == Punctuation && t->Value() == "..")
                                                            {
                                                                IN_Punctiation = false;
                                                                IN_size_c = true;
                                                            }else
                                                                throw SyntaxicError(t->getLineNumber(),t->getColumnNumber()," Mot clé '..' attendu ");
                                                        }
                                                        else
                                                        if(IN_size_c)
                                                        {
                                                            if(t->Nature() == NUMBER)
                                                            {
                                                                size_c = toInt(t->Value());
                                                                IN_size_c = false;
                                                                IN_RI = true;
                                                            }else
                                                                throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Borne supperieur du tableux attendu ");
                                                        }
                                                        else
                                                        if(IN_RI)
                                                        {
                                                            if(t->Nature() == RI)
                                                            {
                                                                IN_RI = false;
                                                                IN_DE_Key = true;
                                                                array  = new Array(QString::fromStdString(id_type).toUpper());
                                                                try{
                                                                    if(f)
                                                                        f->AddType(array);
                                                                    else
                                                                        if(p)
                                                                            p->AddType(array);
                                                                        else
                                                                            Compilateur::ParseTree->AddType(array);
                                                                }catch(std::string error)
                                                                {
                                                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),error);
                                                                }

                                                            }
                                                            else
                                                             if(t->Nature() == Punctuation && t->Value() == ",")
                                                             {
                                                                 IN_Tab = false;
                                                                 IN_ContaintType = false;
                                                                 IN_Mat = true;
                                                                 IN_InitSizeT = true;
                                                                 mat = new MatrixType(QString::fromStdString(id_type).toUpper());
                                                                 try{
                                                                     if(f)
                                                                         f->AddType(mat);
                                                                     else
                                                                         if(p)
                                                                             p->AddType(mat);
                                                                         else
                                                                             Compilateur::ParseTree->AddType(mat);
                                                                 }catch(std::string error)
                                                                 {
                                                                     throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),error);
                                                                 }
                                                             }
                                                            else
                                                                throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle ']' attendu");
                                                        }
                                                        else
                                                        if(IN_DE_Key)
                                                        {

                                                            if(t->Nature() == ID && toUpper(t->Value()) == "DE")
                                                            {
                                                                IN_DE_Key = false;
                                                                IN_ContaintType = true;
                                                            }
                                                            else
                                                                throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle 'DE' attendu");
                                                        }else
                                                        {
                                                            if(t->Nature() == LocationSpecifier)
                                                                memoryRange++;
                                                            else
                                                            if(t->Nature() == ID)
                                                            {
                                                                try {
                                                                 array->setSize(size_c);
                                                                 size_c = 0;
                                                                 TypeOfContaint T;
                                                                 if(f)
                                                                     T = f->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                                                 else
                                                                 if(p)
                                                                     T = p->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                                                 else
                                                                     T = Compilateur::ParseTree->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                                                 T.addMemoryRange(memoryRange);
                                                                 array->setTypeContaint(T);
                                                                 memoryRange = 0;
                                                                 /*
                                                                 if(f)
                                                                     f->AddType(*array);
                                                                 else
                                                                 if(p)
                                                                     p->AddType(*array);
                                                                  else
                                                                     Compilateur::ParseTree->AddType(*array);
                                                                 */
                                                                 //this->currentScope->AddType(*T);                                         

                                                                }catch(std::string error)
                                                                {
                                                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),error);
                                                                }

                                                                IN_Tab = false;
                                                                IN_ContaintType = false;
                                                                IN_Types = false;
                                                                IN_DefType = false;
                                                            }else
                                                                throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Type de contenu du Tableau incorrecte ");

                                                        }
                                                    }
                                            }
                                            else
                                            if(IN_Mat)
                                            {
                                                Mat:{
                                                    int size_l = 0;
                                                    if(IN_InitSizeT)
                                                    {
                                                        if(t->Nature() == NUMBER)
                                                        {
                                                            IN_InitSizeT = false;
                                                            IN_Punctiation = true;
                                                        }else
                                                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Borne inferieur du Matrice attendu ");
                                                    }
                                                    else
                                                    if(IN_Punctiation)
                                                    {
                                                        if(t->Nature() == Punctuation && t->Value() == "..")
                                                        {
                                                            IN_Punctiation = false;
                                                            IN_size_l = true;
                                                        }else
                                                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber()," Mot clé '..' attendu ");
                                                    }
                                                    else
                                                    if(IN_size_l)
                                                    {
                                                        size_l = toInt(t->Value());
                                                        if(t->Nature() == NUMBER)
                                                        {
                                                            IN_size_l = false;
                                                            IN_RI = true;
                                                        }else
                                                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Borne inferieur du Matrice attendu ");
                                                    }
                                                    else
                                                    if(IN_RI)
                                                    {
                                                        if(t->Nature() == RI)
                                                        {
                                                            IN_RI = false;
                                                            IN_DE_Key = true;
                                                        }
                                                        else
                                                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle ']' attendu");
                                                    }
                                                    else
                                                    if(IN_DE_Key)
                                                    {
                                                        if(t->Nature() == ID && toUpper(t->Value()) == "DE")
                                                        {
                                                            IN_DE_Key = false;
                                                            IN_ContaintType = true;
                                                        }
                                                        else
                                                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle 'DE' attendu");
                                                    }else
                                                    {
                                                        if(t->Nature() == LocationSpecifier)
                                                            memoryRange++;
                                                        else
                                                        if(t->Nature() == ID)
                                                        {
                                                            try {
                                                             TypeOfContaint T ;
                                                             if(f)
                                                                 T = f->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                                             else
                                                             if(p)
                                                                 T = p->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                                             else
                                                                 T = Compilateur::ParseTree->getTypeContaint(QString::fromStdString(t->Value()).toUpper());

                                                             T.addMemoryRange(memoryRange);
                                                             memoryRange = 0;
                                                             mat->setRowsCount(size_l);
                                                             size_l = 0;
                                                             mat->setColumnsCount(size_c);
                                                             size_c = 0;
                                                             mat->setTypeContaint(T);
                                                             /*
                                                             if(f)
                                                                 f->AddType(*mat);
                                                             else
                                                             if(p)
                                                                 f->AddType(*mat);
                                                              else
                                                                 Compilateur::ParseTree->AddType(*mat);
                                                              */
                                                             //this->currentScope->AddType(*T);
                                                             //delete mat;
                                                            }catch(std::string error)
                                                            {
                                                                throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),error);
                                                            }
                                                            IN_Types = false;
                                                            IN_Mat = false;
                                                            IN_ContaintType = false;
                                                            IN_DefType = false;
                                                        }else
                                                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Type de contenu du Matrice incorrecte ");
                                                    }
                                                }
                                            }
                                            else
                                            if(IN_Fich)
                                            {
                                                Fich:{
                                                       //qDebug()<< "fich" << t->Value()<<IN_DE_Key<<IN_ContaintType;
                                                        if(IN_DE_Key)
                                                        {
                                                            if(t->Nature() == ID && toUpper(t->Value()) == "DE")
                                                            {
                                                                IN_DE_Key = false;
                                                                IN_ContaintType = true;
                                                                containttype = "";
                                                            }
                                                            else
                                                                throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle 'De' attendu");
                                                        }
                                                        else
                                                        {
                                                            IN_ContaintType = true;
                                                            if(t->Nature() == LocationSpecifier)
                                                                memoryRange++;
                                                            else
                                                            if(t->Nature() == ID)
                                                            {
                                                                try {
                                                                 TypeOfContaint T;
                                                                 try
                                                                 {
                                                                     if(f)
                                                                         T = f->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                                                     else
                                                                         if(p)
                                                                             T = p->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                                                         else
                                                                             T  = Compilateur::ParseTree->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                                                     if(QString::fromStdString(t->Value()).toUpper() == "TEXTE")
                                                                         qDebug()<<"WARNING ("<<t->getLineNumber() << "," << t->getColumnNumber() <<") TYPE UTILISATEUR 'TEXTE' EST IGNORE POUR CETTE FICHIER ";
                                                                 }
                                                                 catch(std::string error)
                                                                 {
                                                                     if(QString::fromStdString(t->Value()).toUpper() == "TEXTE")
                                                                         T = TypeOfContaint("TEXTE");
                                                                     else
                                                                         throw error;
                                                                 }

                                                                 T.addMemoryRange(memoryRange);
                                                                 file->setTypeContaint(T);
                                                                 memoryRange = 0;

                                                                }catch(std::string error)
                                                                {
                                                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),error);
                                                                }

                                                                IN_Fich = false;
                                                                IN_ContaintType = false;
                                                                IN_Types = false;
                                                                IN_DefType = false;

                                                            }
                                                            else
                                                                throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Type de contenu du fichier incorrecte ");

                                                        }

                                                    }
                                            }
                                            else
                                            if(IN_Qalifier)
                                            {
                                                Qalifier:{
                                                    if(t->Nature() == LocationSpecifier)
                                                        memoryRange++;
                                                    else
                                                    if(t->Nature() == ID)
                                                    {

                                                        try{
                                                            TypeOfContaint TQ;
                                                            if(f)
                                                                TQ = f->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                                            else
                                                                if(p)
                                                                    TQ = p->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                                                else
                                                                    TQ = Compilateur::ParseTree->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                                            TQ.addMemoryRange(memoryRange);
                                                            memoryRange = 0;
                                                            QAT->setTypeQalified(TQ);
                                                            /*
                                                            if(f)
                                                                f->AddType(*QAT);
                                                            else
                                                            if(p)
                                                                p->AddType(*QAT);
                                                            else
                                                                Compilateur::ParseTree->AddType(*QAT);
                                                            */
                                                        }catch(std::string error)
                                                        {
                                                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),error);
                                                        }
                                                        IN_DefType = false;
                                                        IN_Qalifier = false;
                                                        IN_Types = false;
                                                    }
                                                    else
                                                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Nom du type qalifier attendu");
                                                }
                                            }

                                      }

                                }

                            }
                    }
                    else
                    {
                        Var:{
                            if(IN_Id_Var)
                            {
                                if(t->Nature() != ID)
                                {
                                    if(t->Nature() == KeyWord)
                                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"'" + t->Value() + "' est un mot reserve algorithmique ");
                                    else
                                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Identificateur du variable incorrecte ");
                                }
                                else
                                {
                                    IN_Id_Var = false;
                                    IN_AssignType = true;
                                    if(listVirtualID.contains(toUpper(t->Value())))
                                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Duplication a trouve suite de declaration du variable '" + t->Value() + "'");
                                    else
                                        listVirtualID << toUpper(t->Value());
                                }
                            }
                            else
                            if(IN_AssignType)
                            {
                                if(t->Nature() == AssignType)
                                {
                                    IN_AssignType = false;
                                    IN_TypeOfVar = true;
                                }
                                else
                                if(t->Nature() == Punctuation && t->Value() == ",")
                                {
                                    IN_AssignType = false;
                                    IN_Id_Var = true;
                                }
                                else
                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot clé ':' attendu mais '" + t->Value() + "' trouvé ");
                            }
                            else
                            {
                                if(t->Nature() == LocationSpecifier)
                                    memoryRange++;
                                else
                                    if(t->Nature() == ID)
                                    {
                                        try{

                                            TypeOfContaint T ;
                                            if(f)
                                                T = f->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                            else
                                            if(p)
                                                T = p->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                            else
                                                T = Compilateur::ParseTree->getTypeContaint(QString::fromStdString(t->Value()).toUpper());

                                            T.addMemoryRange(memoryRange);
                                            memoryRange = 0;
                                            for(int u = 0; u < listVirtualID.size();u++)
                                            {
                                                //qDebug()<<"test : "<< QString::fromStdString( listVirtualID.at(u));
                                                Variable * v = new Variable(QString::fromStdString(listVirtualID[u]),T);
                                                if(f)
                                                   f->AddVariable(*v);
                                                else
                                                if(p)
                                                    p->AddVariable(*v);
                                                else
                                                    Compilateur::ParseTree->AddVariable(*v);

                                                //this->currentScope->AddVariable(*v);
                                                delete v;
                                            }
                                            listVirtualID.clear();

                                        }catch(std::string error)
                                        {
                                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),error);
                                        }
                                        IN_TypeOfVar = false;
                                        IN_Variables = false;
                                    }
                                    else
                                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Type du variable incorrecte ");

                            }
                        }
                    }

            }
            else
            if(IN_Debut)
            {
                // Au bout de IN_HeaderProgram (c à d le mot cle 'DEBUT' a ete detecté ) il va retourne à celui

                if(IN_Fct)
                {
                    //qDebug()<< "In debut fonction  " << t->toString();
                    Statment * debutFct = new Statment();
                    debutFct->SetBehavior((StatmentBehavio)0);
                    Instructions(debutFct,lex);
                    //qDebug()<< "IN END fonction "<<t->toString();
                    IN_Debut = false;
                    IN_Fct = false;
                    IN_HeaderProgram = true;
                    //qDebug()<<"name fct : " << f->getName();
                    Compilateur::ParseTree->AddFunction(*f);
                    f = NULL;
                    //this->currentScope = Compilateur::ParseTree;
                }
                else
                if(IN_Proc)
                {
                   // qDebug()<< "In debut Procedure " << t->toString();
                    Statment * debutProc = new Statment();
                    debutProc->SetBehavior((StatmentBehavio)0);
                    Instructions(debutProc,lex);
                    //qDebug()<< "IN END Procedure "<<t->toString();
                    IN_Debut = false;
                    IN_Proc = false;
                    IN_HeaderProgram = true;
                    //qDebug()<<"name proc : " << p->getName();
                    Compilateur::ParseTree->AddProcedure(*p);
                    p = NULL;
                    //this->currentScope = Compilateur::ParseTree;
                }
                else
                {
                    //+ INCLURE LES FONCTION ET LES PROCEDURES DES EXTENTIONS


                    //- INCLURE LES FONCTION ET LES PROCEDURES DES EXTENTIONS
                    //qDebug()<< "In debut Algorithme " << t->toString();
                    Statment * debAlgo = new Statment();
                    Instructions(debAlgo,lex);
                    //qDebug()<< "IN END Algorithme "<<t->toString();
                    IN_Debut = false;
                    return;
                }

            }
            else
            if(IN_Fct)
            {
                //qDebug()<< "In Fonction" << QString::fromStdString(t->Value()) << IN_id_fct << IN_Lp << IN_listArgs <<  IN_Rp << IN_AssignType;

                if(IN_id_fct)
                {
                    if(t->Nature() != ID)
                    {
                        if(t->Nature() == KeyWord)
                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"'" + t->Value() + "' est un mot reserve algorithmique ");
                        else
                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"identificateur du fonction incorrecte ");
                    }
                    else
                    {
                        f->setName(QString::fromStdString(t->Value()).toUpper());
                        IN_id_fct = false;
                        IN_Lp  = true;
                    }
                }
                else
                if(IN_Lp)
                {
                    if(t->Nature() != Lp)
                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle ' ( ' attendu ");
                    else
                    {
                        IN_Lp = false;
                        IN_listArgs = true;
                        IN_ES = true;
                    }
                }
                else
                if(IN_listArgs)
                {
                    if(t->Nature() == Rp && IN_ES && !require)
                    {
                        IN_listArgs = false;
                        require = false;
                        IN_IdArg = false;
                        IN_Rp = true;
                        goto ReloadAll;
                    }
                    listArgs:{
                        if(IN_ES)
                        {
                            arg = new Argment();
                            if(toUpper(t->Value()) == "DON" || toUpper(t->Value()) == "RES" || toUpper(t->Value()) == " DONRES" || toUpper(t->Value()) == "DON_RES")
                            {
                                if(IN_Fct)
                                {
                                    if(toUpper(t->Value()) != "DON")
                                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber()," Mode du passage interdit ");
                                    else
                                    {
                                       arg->setIO(IN);
                                    }
                                }else
                                {
                                    if(toUpper(t->Value()) == "RES")
                                        arg->setIO(OUT);
                                    else
                                    if(toUpper(t->Value()) == "DONRES" || toUpper(t->Value()) == "DON_RES")
                                        arg->setIO( IN_OUT );
                                    else
                                        arg->setIO(IN);
                                }
                                IN_ES = false;
                                IN_IdArg = true;
                            }
                            else                             
                            {
                                arg->setIO(IN);
                                IN_ES = false;
                                IN_IdArg = true;
                                goto ReloadAll;
                            }
                        }
                        else
                        if(IN_IdArg)
                        {
                            if(t->Nature() != ID)
                            {
                                if(t->Nature() == KeyWord)
                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"'" + t->Value() + "' est un mot reserve algorithmique ");
                                else
                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Identificateur d'argument incorrecte " + t->Value());
                            }
                            else
                            {
                                arg->setName(QString::fromStdString(toUpper(t->Value())));
                                IN_IdArg = false;
                                IN_AssignType = true;
                            }
                        }
                        else
                        if(IN_AssignType)
                         {
                             if(t->Nature() != AssignType)
                                 throw SyntaxicError(t->getLineNumber(),t->getColumnNumber()," mot cle ':' attendu  ");
                             else
                             {
                                 IN_AssignType = false;
                                 IN_typeOfArg = true;
                             }
                         }
                        else
                        if(IN_typeOfArg)
                         {
                            if(t->Nature() == LocationSpecifier)
                                memoryRange++;
                            else
                            {
                                try
                                {
                                    TypeOfContaint T ;
                                    if(f)
                                        T = f->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                    else
                                    if(p)
                                        T = p->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                    else
                                        T = Compilateur::ParseTree->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                                    //Type T = currentScope->getType();
                                    T.addMemoryRange(memoryRange);
                                    memoryRange = 0;
                                    arg->setType(T);
                                    if(IN_Fct)
                                        f->addArg(*arg);
                                    else
                                        p->addArg(*arg);
                                    arg = NULL;

                                }catch(std::string error)
                                {
                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),error);
                                }
                                require = false;
                                IN_typeOfArg = false;
                            }
                         }
                        else
                         {
                             if(t->Value() == ",")
                             {
                                 IN_ES = true;
                                 require = true;
                             }
                             else
                             {
                                 IN_listArgs = false;
                                 IN_IdArg = false;
                                 IN_Rp = true;
                                 require = false;
                                 goto ReloadAll;
                             }

                         }

                    }//listArgs
                }
                else
                if(IN_Rp)
                {
                    if(t->Nature() != Rp)
                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle ')' attendu ");
                    else
                    {
                        IN_Rp = false;
                        IN_AssignType = true;
                    }
                }
                else
                if(IN_AssignType)
                {
                    if(t->Nature() != AssignType)
                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle ':' attendu ");
                    else
                     {
                        IN_AssignType = false;
                        IN_returnType = true;
                     }
                }
                else
                if(IN_returnType)
                {
                    if(t->Nature() == LocationSpecifier)
                        memoryRange++;
                    else
                    if(t->Nature() == ID)
                    {
                        try{
                            TypeOfContaint T ;
                            if(f)
                                T = f->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                            else
                            if(p)
                                T = p->getTypeContaint(QString::fromStdString(t->Value()).toUpper());
                             else
                                T = Compilateur::ParseTree->getTypeContaint(QString::fromStdString(t->Value()).toUpper());

                            //this->currentScope->getType(QString::fromStdString(t->Value()).toUpper());
                            T.addMemoryRange(memoryRange);
                            memoryRange = 0;
                            f->setReturnType(T);
                        }catch(std::string error)
                        {
                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),error);
                        }

                        IN_returnType = false;
                        IN_HeaderProgram = true;
                    }
                    else
                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"type de retour de fonction incorrecte ");
                }else
                {
                    IN_HeaderProgram = true;
                    //this->currentScope = f;
                    //  if(toUpper(t->Value()) != id_fct && t->Value() != ".")goto ReloadAll;
                }

            }
            else
            if(IN_Proc)
            {
                if(IN_IdProc)
                {
                    if(t->Nature() != ID)
                    {
                        if(t->Nature() == KeyWord)
                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"'" + t->Value() + "' est un mot reserve algorithmique ");
                        else
                            throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"identificateur du procedure incorrecte ");
                    }
                    else
                    {
                        p->setName(QString::fromStdString(toUpper(t->Value())));
                        IN_IdProc = false;
                        IN_Lp  = true;
                    }
                }
                else
                if(IN_Lp)
                {
                    if(t->Nature() != Lp)
                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle ' ( ' attendu ");
                    else
                    {
                        IN_Lp = false;
                        IN_listArgs = true;
                        IN_ES = true;
                    }
                }
                else
                if(IN_listArgs)
                {
                    goto listArgs;
                }
                else
                if(IN_Rp)
                {
                    if(t->Nature() != Rp)
                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle ')' attendu ");
                    else
                    {
                        IN_Rp = false;
                        IN_HeaderProgram = true;
                    }
                }
                else
                {
                    //this->currentScope = p;
                    IN_HeaderProgram = true;
                    //if(toUpper(t->Value()) != id_proc && t->Value() != ".") goto ReloadAll;
                }
            }
            else
            {
                /*if(IN_Fct)
                {
                    qDebug()<< "In END fonction  ";
                    if(toUpper(t->Value()) != id_fct && t->Value() != ".")
                    {
                        IN_HeaderProgram = true;
                        goto ReloadAll;
                    }
                    else
                    {
                        IN_HeaderProgram = true;
                    }
                    IN_Fct = false;

                }
                else
                if(IN_Proc)
                {
                    qDebug()<< "In END Procedure ";
                    if(toUpper(t->Value()) != id_proc && t->Value() != ".")
                    {
                        IN_HeaderProgram = true;
                        goto ReloadAll;
                    }
                    else
                    {
                        IN_HeaderProgram = true;
                    }
                    IN_Proc = false;
                    //if(toUpper(t->Value()) != id_proc && t->Value() != ".") goto ReloadAll;

                }
                else
                {
                    // include les fonctions et procecures ici
                    qDebug()<<QString::fromStdString(t->Value()) << "In END Algorithme ";
                }
                */
            }
        }
        t = lex->NextToken();
    }
    if(IN_Id_Algo)
    {
        if(IN_Algorithme)
            throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle Algorithme attendu");
        else
            throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Identificateur du programme attendu");
        // INFORMATION INCOPMLETE PROGRAM
    }
    else
    if(IN_Directives && !IN_Extention)
    {
        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Nom d'extention attendu");
        // INFORMATION INCOPMLETE PROGRAM
    }
    else
    if(IN_HeaderProgram)
    {
        if(IN_Constantes)
        {
            if(IN_IDConst)
                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Identificateur du constante attendu");
            else
            if(IN_OperatorConst)
                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle '=' attendu");
            else
            if(IN_ConstValue)
                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Valeur du constante attendu");
            else
                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Debut du programme attendu");

        }
        else
        if(IN_Types)
        {
            if(IN_Id_Type)
                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Identificateur du type attendu");
            else
            if(IN_OpertatorType)
                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle '=' attendu");
            else
            if(IN_DefType)
            {
                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Deffinition du type attendu");
            }
            else
            if(IN_Enreg)
            {
                if(IN_ID_Field)
                    throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Identificateur du champ d'enregistrement attendu");
                else
                if(IN_AssignType)
                    throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle ':' attendu");
                else
                if(IN_typeOfField)
                     throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Type de champ d'enregistrement attendu");
                else
                     throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Fin d'enregistrement attendu");
            }
            else
            if(IN_Tab)
            {
                if(IN_LI)
                    throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Deffinition du tableau attendu");
                else
                if(IN_InitSizeT)
                    throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Valeur initial du tableau attendu");
                else
                if(IN_Punctiation)
                     throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle '..' attendu");
                else
                if(IN_size_c)
                     throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Taille du tableau attendu");
                else
                if(IN_RI)
                     throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle ']' attendu");
                else
                if(IN_DE_Key)
                     throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle de attendu");
                else
                     throw SyntaxicError(lex->currentLine(),lex->currentColumn()," Type de contenu du tableau attendu");
            }
            else
            if(IN_Mat)
            {
                if(IN_LI)
                     throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Deffinition du Matrice attendu");
                else
                if(IN_InitSizeT)
                     throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Valeur initial du Matrice attendu");
                else
                if(IN_Punctiation)
                     throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle '..' attendu");
                else
                if(IN_size_c)
                     throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Taille du Matrice attendu");
                else
                if(IN_size_l)
                     throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Nombre de conlonnes du Matrice attendu");
                else
                if(IN_RI)
                    throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle ']' attendu");
                else
                if(IN_DE_Key)
                    throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle de attendu");
                else
                    throw SyntaxicError(lex->currentLine(),lex->currentColumn()," Type de contenu du tableau attendu");
            }
            else
            if(IN_Fich)
            {
                if(IN_DE_Key)
                     throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle 'DE' attendu");
                else
                      throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Type de contenu du fichier attendu");

            }
            else
               throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Debut du programme attendu");
        }
        else
        if(IN_Variables)
        {
            if(IN_Id_Var)
                  throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Identificateur du variable attendu");
            else
            if(IN_AssignType)
                  throw SyntaxicError(lex->currentLine(),lex->currentColumn()," ':' attendu ");
            else
                  throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Type du variable attendu");
        }
        else
             throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Debut du programme attendu");
        // INFORMATION INCOPMLETE PROGRAM
    }
    else
    if(IN_Fct)
    {
        if(IN_id_fct)
             throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Identificateur du fonction attendu");
        else
        if(IN_Lp)
             throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"'(' attendu");
        else
        if(IN_listArgs)
        {
            if(IN_IdArg)
              throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Identificateur d'argument attendu");
            else
            if(IN_AssignType)
               throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"':' attendu");
            else
            if(IN_typeOfArg)
               throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Type d'argument attendu");
            else
               throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"')' attendu");
        }
        else
        if(IN_Rp)
              throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"')' attendu");
        else
        if(IN_AssignType)
             throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"':' attandu");
        else
             throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Type de retour de fonction attendu");
    }
    else
    if(IN_Proc)
    {
        if(IN_IdProc)
             throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Identificateur du procedure attendu");
        else
        if(IN_Lp)
             throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"'(' attendu");
        else
        if(IN_listArgs)
        {
            if(IN_IdArg)
               throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Identificateur d'argument attendu");
            else
            if(IN_AssignType)
               throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"':' attendu");
            else
            if(IN_typeOfArg)
               throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Type d'argument attendu");
            else
               throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"')' attendu");
        }
        else
              throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"')' attendu");
    }
    else
    if(IN_Debut)
    {
        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Fin du programme attendu attendu");
    }

}

void SyntaxicAnalyser::Instructions(Statment * parentstatment,LexicalAnalyser * lex)
{       
    bool IN_Instrictions = false;
    bool IN_Si         = false;

    bool IN_Pour       = false;
    bool IN_Reference  = false;
    bool IN_TO_FOR     = false;
    bool IN_Vi         = false;
    bool IN_Vf         = false;
    bool IN_Pas        = false;
    bool IN_Faire      = false;

    bool IN_TanteQue   = false;
    bool IN_Repeter    = false;
    bool IN_Selon      = false;
    bool IN_returnFct  = false;
    bool IN_CallProc   = false;
    bool IN_With       = false;

    bool IN_Expression = false;
    bool IN_Alors      = false;
    bool IN_Else       = false;
    bool IN_Affectation= false;
    bool IN_End        = false;


    Token * t = NULL;

    while ((t = lex->NextToken())) {
    ReloadAll:{
            if(IN_Si == false && IN_Pour == false && IN_TanteQue == false && IN_Repeter == false && IN_Selon == false && IN_returnFct == false && IN_CallProc == false && IN_With == false && IN_Else == false)
            {
                if(toUpper(t->Value()) == Si)
                {
                    IN_Si = true;
                    IN_Expression = true;
                }
                else
                if(toUpper(t->Value()) == Pour )
                {
                    IN_Pour = true;
                    IN_Reference = true; // POUR LE COMPTEUR
                }
                else
                if(toUpper(t->Value()) == TanteQue)
                {
                    IN_TanteQue = false;
                    IN_Expression = true;
                }
                else
                if(toUpper(t->Value()) == Repeter)
                {
                    IN_Repeter = true;

                }
                else
                if(toUpper(t->Value()) == Selon )
                {
                    IN_Selon = true;
                    IN_Vi = true;
                }
                else
                if(toUpper(t->Value()) == Avec)
                {

                }
                if(toUpper(t->Value()) == FIN)
                {
                    return;
                }
                else
                if(t->Nature() == ID)
                {
                    Identificateur id = checkBehaviorID(t);
                    /*if(id.behavior == id_procedure)
                    {
                        IN_CallProc = true;
                        goto ReloadAll;
                    }
                    else
                    if(IN_Fct && id.behavior == id_Fucntion)
                    {
                        In_re
                    }*/
                    // Affectation | Procedure Call | Return fucntion
                }
            }
            if(IN_Si)
            {
               if(toUpper(t->Value()) == "NON")
               {
                   IN_Si = false;
                   IN_Else = true;
                   if(1) // SI L INSTRUCTION MERE EST SI ALORS
                   {
                       Statment * elseStatment = new Statment();
                       Instructions(elseStatment,lex);
                   }else
                       throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Instruction 'SI NON' male utilisé ");
               }
               if(IN_Expression)
               {
                    // TRAITEMENT D EXPRESSION
                   IN_Expression = false;
                   IN_Alors = true;
               }
               else
               if(IN_Alors)
               {
                  if(toUpper(t->Value()) == Alors)
                  {
                      IN_Alors = false;
                      IN_Instrictions = true;
                  }
               }
               else
               {

               }
            }
            else
            if(IN_Pour)
            {
               if(IN_Reference)
               {
                   if(t->Nature() == LocationSpecifier)
                   {
                       id_compteur.append(toUpper(t->Value()));
                       Instructions(parentstatment,lex);
                   }
                   else
                   if(t->Nature() == ID)
                   {
                       id_compteur.append(toUpper( t->Value()));
                       IN_Reference = false;
                       IN_TO_FOR = true;
                   }
                   else
                       throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"identificateur du compteur du boucle POUR incorrecte ");

               }
            }
            else
            if (IN_TanteQue)
            {
                if(IN_Expression)
                {
                    // TRAITEMNT D EXPRESSION JUSQU A 'FAIRE'
                    IN_Expression = false;
                }
                else
                if(IN_Faire)
                {
                    if(toUpper(t->Value()) == Faire)
                    {
                        //
                        Statment * whilest = new Statment();
                        //Instructions(whilest,lex);
                    }else
                        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle 'FAIRE ' Attendu ");

                }
                else
                if(toUpper(t->Value()) == TanteQue)
                {
                    IN_TanteQue = false;
                }
                else
                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle 'FIN TANTEQUE ' Attendu ");

            }
            else
            if (IN_Repeter)
            {
                Statment * repeat = new Statment();
                Instructions(repeat,lex);
                // expression
                Expression * ex = AnalyseExpression(lex);
                t = previeusToken;
                goto ReloadAll;

                // ...
            }
            else
            if (IN_Selon)
            {

            }
            else
            if (IN_returnFct)
            {

            }
            else
            if (IN_CallProc)
            {

            }
            else
            if (IN_With)
            {

            }
            else
            {

            }
        }
    }

    if /*_*/(IN_Si) {
        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Syntaxe incorrecte 'SI..ALORS'  ");
    }
    else if (IN_Pour){
        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Syntaxe incorrecte 'Pour .. FAIRE' ");
    }
    else if (IN_TanteQue){
        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Syntaxe incorrecte 'Tanteque .. FAIRE' ");
    }
    else if (IN_Repeter){
        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Syntaxe incorrecte 'Repeter .. Jusqu_a' ");

    }
    else if (IN_Selon){
        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Syntaxe incorrecte 'Selon .. Faire' ");

    }
    else if (IN_returnFct){
        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Syntaxe incorrecte 'Retourn fct' ");

    }
    else if (IN_CallProc){
        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Syntaxe incorrecte 'call proc' ");

    }
    else if (IN_With){
        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Syntaxe incorrecte 'Avec .. Faire' ");

    }
    else if (IN_Else) {
        throw SyntaxicError(t->getLineNumber(),t->getColumnNumber()," Syntaxe incorrecte 'SI NON ..' ");
    }
    else
    if(t)   // SI 'FIN'EST DETECTE OU NON
    {
        if(parentstatment->GetBehavior() != (StatmentBehavio)0) // SI LA MERE EST DIFFERENT A L'INSTRUCTION MERE ('DEBUT')
        {
            if((t = lex->NextToken()))
              {
                    switch (parentstatment->GetBehavior()) {
                    case FOR   :if(toUpper(t->Value()) != Pour)
                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle 'FIN POUR' attendu ");
                        break;
                    case WHILE :if(toUpper(t->Value()) != TanteQue)
                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle 'TANTEQUE' attendu ");
                        break;
                    case REPEAT:if(toUpper(t->Value()) != Jusqu_A)
                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle 'JUSQU_A' attendu ");
                                else
                                {
                                    // expression
                                }
                        break;
                    case IF    :
                    case ELSE  :if(toUpper(t->Value()) != Si)
                                    throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle 'FIN SI' attendu ");
                        break;
                    case With  :
                    case CALL_PROCEDURE:break;
                    default:
                        break;
                    }
                    return;
             }

        }
        else // EN CAS DE L'INSTRUCTION MERE ('DEBUT')
            return;
    }
    // EN DE L'INSTRUCTION MERE ('DEBUT') N 'EST PAS ENCORE DETECTE
    //throw SyntaxicError(t->getLineNumber(),t->getColumnNumber(),"Mot cle 'FIN' attendu ");
}

Expression * SyntaxicAnalyser::AnalyseExpression(LexicalAnalyser *lex)
{
    bool IN_Expression              = false;
        bool IN_ExpressionOperator  = false;

    bool IN_reference               = false;
    bool IN_ConstValue              = false;
    bool IN_CallFunction            = false;
        bool IN_EffectefArgs        = false;
        bool IN_EffectArg           = false;

    // UTILISATION DOIT ETRE RECURSIVE ...
    Expression * expression = NULL;
    Token *t = lex->NextToken();
    FctCall * fctcall = NULL;
    previeusToken = t;

    while (t) {

        ReloadAll:{
            if (t->getLineNumber() != previeusToken->getLineNumber() || t->Nature() == Rp)
            {
                qDebug()<<"fin du ligne d 'expression "<<t->toString();
                goto EndExpression;
            }
            else
            if (!IN_Expression && !IN_ExpressionOperator)
            {
                if(expression == NULL)
                {
                    IN_Expression = true;
                    goto _Expression;
                }
                else
                {
                    IN_ExpressionOperator = true;
                    goto ExpressionOperator;
                }
            }
            else
            if (IN_ExpressionOperator)
            {
                ExpressionOperator:{
                    qDebug()<<"IN_Expression_Operator "<<t->toString();
                    if(listExOPerators.contains(t->Value()) )
                    {
                        if(!expression->hasExpressionOperator())
                        {
                            Expression::ExpressionOperator *operatorExp = new Expression::ExpressionOperator();

                            operatorExp->value = t;
                            operatorExp->FirstOperand = expression;
                            operatorExp->SecondOperand = AnalyseExpression(lex);
                            if(operatorExp->SecondOperand == NULL)
                                Error(t," Expression incomplete  : seconde argument de l'operateur utlise est attendu ");
                            expression->setExpressionOperator(operatorExp);

                            return expression;
                        }
                        else
                            Error(t," Duplication d 'operateur d 'expression ");
                    }
                    else
                    {
                        EndExpression:{
                            if(expression == NULL)
                            {
                                Error(t,"Expression vide interdit dans ce traitement");
                            }
                            else
                            if(expression->hasExpressionOperator())
                            {
                                if(expression->getExpressionOperator()->SecondOperand == NULL)
                                    Error(t,"Expression incomplete");
                            }
                            return expression;
                            // FIN D ANALYSE AVEC SUCCEE
                        }
                    }
                }
            }
            else
            if (IN_Expression)
            {
                _Expression:{
                    qDebug()<<"IN_Expression "<< t->toString();
                    if (!IN_reference && !IN_CallFunction && !IN_ConstValue)
                    {
                        if(t->Nature() == ID)
                        {
                            IN_reference = true;
                            goto _Reference;
                        }
                        else
                        if(t->Nature() == KeyWord && t->Value() == FN)
                        {
                            IN_CallFunction = true;
                            IN_id_fct = true;
                          //goto CallFunction;
                        }
                        else
                        if(t->Nature() == Reel || t->Nature() == NUMBER || t->Nature() == STR || t->Nature() == CHAR || toUpper(t->Value()) == "VRAI" || toUpper(t->Value()) == "FAUX")
                        {
                            IN_ConstValue = true;
                            goto _ConstValue;
                        }
                        else
                        if(listExOPerators.contains(t->Value()))
                        {
                            Error(t,"Erreur fatale : Une reference ou un valeur attendu pour effectuer l 'expression ");
                        }
                        else
                            Error(t,"Erreur fatale : Le mot '" + t->Value() + "' n est pas une reference ou un valeur a comparer par opertauer ");
                    }
                    else
                    if (IN_reference)
                    {
                        _Reference:{
                            qDebug()<< "( A-Ex ))IN_Reference"<<t->toString();
                            previeusToken = t;
                            expression = GetReference(lex);
                            IN_Expression = false;
                            IN_reference = false;
                            IN_ExpressionOperator = true;
                        }
                    }
                    else
                    if (IN_CallFunction)
                    {
                        CallFunction:{
                            qDebug()<< "( A-Ex ))IN_CallFct "<<t->toString();
                            if(IN_id_fct)
                            {
                                if(t->Nature() == ID)
                                {
                                    fctcall = new FctCall(t->Value());
                                    IN_id_fct = false;
                                    IN_Lp = true;
                                }
                                else
                                    Error(t,"Identificateur de fonction a apeller attendu");
                            }
                            else
                            if(IN_Lp)
                            {
                                if(t->Nature() == Lp)
                                {
                                    IN_Lp = false;
                                    IN_EffectefArgs = true;
                                    IN_EffectArg  = true;
                                }
                                else
                                    Error(t,"Appelle manque effectice parametres FN .. (.,.)");
                            }
                            else
                            if(IN_Rp)
                            {
                                if(t->Nature() == Rp)
                                {
                                    IN_Rp = false;
                                    IN_CallFunction = false;
                                    IN_Expression = false;
                                    IN_ExpressionOperator = true;

                                    return fctcall;
                                }
                            }
                            else
                            if(IN_EffectefArgs)
                            {
                                if(t->Nature() == Rp)
                                {
                                    IN_EffectefArgs = false;
                                    IN_EffectArg = false;
                                    return fctcall;
                                }

                                ListEfArgs:
                                {
                                    if(IN_EffectArg)
                                    {
                                        Expression * effectArg = AnalyseExpression(lex);
                                        fctcall->AddEffectArg(effectArg);
                                    }
                                    else
                                    if(IN_Punctiation)// I MEAN ',' ARGMENTS SEPARATOR
                                    {
                                        if(t->Value() == ",")
                                        {
                                            IN_Punctiation = false;
                                            IN_EffectArg = true;
                                        }
                                        else
                                        {
                                            IN_Rp = true;
                                            IN_Punctiation = false;
                                            goto ListEfArgs;
                                        }
                                    }
                                }
                            }
                            else
                            {

                            }
                        }
                    }
                    else
                    if (IN_ConstValue)
                    {
                        _ConstValue:{
                            qDebug()<< "( A-Ex ))IN_ConstValue "<<t->toString();
                            expression = new ConstValue(t);
                            IN_ConstValue = false;
                            IN_Expression = false;
                            IN_ExpressionOperator = true;
                        }
                    }
                }
            }

        }

        previeusToken = t;
        t = lex->NextToken();
    }
     return expression;
}

Reference *SyntaxicAnalyser::GetReference(LexicalAnalyser *lex)
{
    Token *t = previeusToken;
    Reference * ref = NULL;
    bool IN_IdRef               = true;
    bool IN_ByteOperator        = false;
    bool IN_FieldRecord         = false;
    bool IN_Indexing            = false;
    qDebug()<<"IN FCT GETREFERENCE"<<t->toString();
    while (t) {
        ReloadAll:{
            if(!IN_IdRef && !IN_ByteOperator)
            {
                if(ref == NULL)
                {
                    IN_IdRef = true;
                    goto IDRef;
                }
                else
                if(listByteOpertors.contains(toUpper(t->Value())))
                {
                    IN_ByteOperator = true;
                    goto _ByteOperator;
                }
                else
                {

                }
            }
            else
            if(IN_IdRef)
            {
                IDRef:{
                    qDebug()<<"IN_IdReference"<<t->toString() ;
                    if(t->Nature() == ID)
                    {
                        ref->setValue(t);
                        IN_IdRef = false;
                        IN_ByteOperator = true;
                    }
                    else
                        Error(t,"Un identificateur attendu");
                }
            }
            else
            if(IN_ByteOperator)
            {
                _ByteOperator:{
                    qDebug()<<"IN_byteOperator"<<t->toString();
                    if(t->Nature() == LocationSpecifier)
                    {
                        Reference::ByteOperator op;
                        op.value = t;
                        op.FirstOperand = ref;

                        if(op.value->Value() == ".")
                            op.SecondOperand = GetReference(lex);
                        else
                        if(op.value->Value() == "[")
                        {
                            op.SecondOperand = AnalyseExpression(lex);
                            if(op.SecondOperand == NULL)
                                Error(t,"Index attendu [index]");

                        }
                        else // "@"
                        {

                        }
                        if(op.SecondOperand == NULL)
                        {
                            Error(t,"Reference incomplete ");
                        }
                    }
                    else
                    if(t->Value() == "[")
                    {
                        Reference::ByteOperator op;
                        op.FirstOperand = ref;
                        op.value = t;
                        op.SecondOperand = AnalyseExpression(lex);
                        t = previeusToken;
                        ref->setByteOperator(&op);

                        if(t->Value() != "]")
                            Error(t,"']' attendu");
                        return ref;
                    }
                    else
                    if(t->Value() == ".")
                    {
                        Reference::ByteOperator op;
                        op.FirstOperand = ref;
                        op.value = t;
                        op.SecondOperand = GetReference(lex);
                        t = previeusToken;
                        ref->setByteOperator(&op);

                        return ref;
                    }
                    else
                    {
                        t = previeusToken;
                        return ref;
                    }
                }
                // IF TOKEN IS BYTE OPERATOR SET IT ORWISE GOTO CHEKING IF IS CALL FUCNTION OR OPERTOR EXPRESSION
            }
        }
        previeusToken = t;
        t = lex->NextToken();

    }
    return ref;
}

Identificateur SyntaxicAnalyser::checkBehaviorID(Token *token)
{
    if(token->Nature() != ID)
        throw SyntaxicError(token->getLineNumber(),token->getColumnNumber(),"'" + token->Value() + "' n est un identificateur ");
    
    Identificateur id;
    id.value = toUpper(token->Value());
    id.token = *token;
     if(IN_Proc)
        {
             if(p->hasArg(QString::fromStdString(id.value)))
                 id.behavior = id_argment;
             else
             if(p->hasConstant(QString::fromStdString(id.value)))
                 id.behavior = id_constante;
             else
             if(p->hasType(QString::fromStdString(id.value)))
                 id.behavior = id_Type;
             else
             if(p->hasVariable(QString::fromStdString(id.value)))
                 id.behavior = id_variable;
             else
             if(Compilateur::ParseTree->hasFunction(QString::fromStdString(id.value)))
             {
                 id.behavior = id_Fucntion;
             }
             else
             if(Compilateur::ParseTree->hasProcedure(QString::fromStdString(id.value)))
             {
                 id.behavior = id_procedure;
             }
             else
                 throw SyntaxicError(token->getLineNumber(),token->getColumnNumber(),"identificateur '" + token->Value() + "' n est pas declare dans ce programme ");
         }
     else
     if(IN_Fct)
         {
             if(f->hasArg(QString::fromStdString(id.value)))
                 id.behavior = id_argment;
             else
             if(f->hasConstant(QString::fromStdString(id.value)))
                 id.behavior = id_constante;
             else
             if(f->hasType(QString::fromStdString(id.value)))
                 id.behavior = id_Type;
             else
             if(f->hasVariable(QString::fromStdString(id.value)))
                 id.behavior = id_variable;
             else
             if(Compilateur::ParseTree->hasFunction(QString::fromStdString(id.value)))
             {
                 id.behavior = id_Fucntion;
             }
             else
                 throw SyntaxicError(token->getLineNumber(),token->getColumnNumber(),"identificateur '" + token->Value() + "' n est pas declare dans ce programme ");
         }
     else
         {
             if(Compilateur::ParseTree->hasConstant(QString::fromStdString(id.value)))
                 id.behavior = id_constante;
             else
             if(Compilateur::ParseTree->hasType(QString::fromStdString(id.value)))
                 id.behavior = id_Type;
             else
             if(Compilateur::ParseTree->hasVariable(QString::fromStdString(id.value)))
                 id.behavior = id_variable;
             else
             if(Compilateur::ParseTree->hasFunction(QString::fromStdString(id.value)))
             {
                 id.behavior = id_Fucntion;
             }
             else
             if(Compilateur::ParseTree->hasProcedure(QString::fromStdString(id.value)))
             {
                 id.behavior = id_procedure;
             }
             else
                 throw SyntaxicError(token->getLineNumber(),token->getColumnNumber(),"identificateur '" + token->Value() + "' n est pas declare dans ce programme ");

         }
     return id;
    
}

void SyntaxicAnalyser::XMLAnalyse(QDomDocument source)
{
    this->source = source;
    this->XMLAnalyse();
}

void SyntaxicAnalyser::XMLAnalyse()
{
    /// ################################## //
    ///     ANALYSE EN TETE ALGORITHME
    /// ################################## //

    int ligne = 1;
    ScaneHeaderXMLScope(source.documentElement(),Compilateur::ParseTree,&ligne);
    // fonctions
    QDomElement rootfcts = source.documentElement().firstChildElement("fonctions");
    if(rootfcts.hasChildNodes())
    {
        ligne++;
        QDomNodeList listfcts = rootfcts.elementsByTagName("fct");
        for(int i = 0; listfcts.size();i++)
        {
            QDomElement elmfct = listfcts.at(i).toElement();
            QString fctname = elmfct.attribute("name");
            TypeOfContaint typretour = Compilateur::ParseTree->getTypeContaint(elmfct.attribute("type"));
            // try
            {
                //LexicalAnalyser::isIdToken(fctname);
            }
            // catching lexical error
            Function fct(fctname,typretour);
                //fct.extandsTypes(Compilateur::ParseTree->getTypes());

            QDomNodeList listargs = elmfct.elementsByTagName("para");
            for(int i = 0; i < listargs.size();i++)
            {
                QDomElement elmarg = listargs.at(i).toElement();

                QString namearg = elmarg.attribute("name");
                QString stringtypearg = elmarg.attribute("type");
                IOArgment io =  (IOArgment)elmarg.attribute("passage").toInt();
                // try
                {
                    //LexicalAnalyser::isIdToken(namearg);
                }
                // catching lexical error

                TypeOfContaint typearg = Compilateur::ParseTree->getTypeContaint(stringtypearg);

                Argment arg(namearg,typearg,io);
                try{
                    fct.addArg(arg);
                }catch(SyntaxicError e)
                {
                    this->Handle_Error(ligne,e);
                }
            }
            Compilateur::ParseTree->AddFunction(fct);
            ScaneHeaderXMLScope(elmfct,&fct,&ligne);
            ScaneCoreXMLScope(elmfct,&fct,&ligne);
        }
    }
    // procedures
    QDomElement rootPrcds = source.documentElement().firstChildElement("procedures");
    if(rootPrcds.hasChildNodes())
    {
        ligne++;
        QDomNodeList listprcd = rootPrcds.elementsByTagName("proc");
        for(int i = 0; listprcd.size();i++)
        {
            QDomElement elmprcd = listprcd.at(i).toElement();
            QString prcdname = elmprcd.attribute("name");

            //LexicalAnalyser::isIdToken(prcdname);

            Procedure procedure (prcdname);
            //procedure.extandsTypes(Compilateur::ParseTree->getTypes());

            QDomNodeList listargs = elmprcd.elementsByTagName("para");
            for(int i = 0; i < listargs.size();i++)
            {
                QDomElement elmarg = listargs.at(i).toElement();

                QString namearg = elmarg.attribute("name");
                QString stringtypearg = elmarg.attribute("type");
                IOArgment io =  (IOArgment)elmarg.attribute("passage").toInt();
                // try
                {
                    //LexicalAnalyser::isIdToken(namearg);
                }
                // catching lexical error

                TypeOfContaint typearg = Compilateur::ParseTree->getTypeContaint(stringtypearg);

                Argment arg(namearg,typearg,io);
                try{
                    procedure.addArg(arg);
                }catch(SyntaxicError e)
                {
                    this->Handle_Error(ligne,e);
                }
            }
            Compilateur::ParseTree->AddProcedure(procedure);
            ScaneHeaderXMLScope(elmprcd,&procedure,&ligne);
            ScaneCoreXMLScope(elmprcd,&procedure,&ligne);
        }
    }
    ScaneCoreXMLScope(source.documentElement(),Compilateur::ParseTree,&ligne);
}

void SyntaxicAnalyser::ScaneCoreXMLScope(QDomElement root, Scope *scope, int *ligne)
{
    // ------------------- CORE SCOPE -----------
    QDomElement rootStatments = root.firstChildElement("Debut");
    if(rootStatments.hasChildNodes())
    {
        QDomNodeList xmlStatments = root.elementsByTagName("item");
        for(int i = 0 ; i < xmlStatments.size();i++)
        {
            QDomElement xmlstatment = xmlStatments.at(i).toElement();
            Statment * statment;
            ScaneXMLStatment(xmlstatment,statment,ligne);
        }
    }
}

void SyntaxicAnalyser::ScaneHeaderXMLScope(QDomElement root, Scope *scope, int * ligne)
{
    scope->setName(root.attribute("name"));
    // ------------------- CONSTANTES -----------
    QDomElement constantesroot = root.firstChildElement("constantes");
    if(constantesroot.hasChildNodes())
    {
        QDomNodeList listconsts = constantesroot.elementsByTagName("const");
        ligne++;
        for (int i = 0; i < listconsts.count();i++)
        {
            ligne++;
            QDomElement elmnode = listconsts.at(i).toElement();
            QString nomconst = elmnode.attribute("name"),valeur = elmnode.attribute("valeur");
            try{
                //LexicalAnalyser::isIdToken(nomconst);
            }catch(SyntaxicError e)
            {
                emit this->Handle_Error(*ligne,e);
            }

            if(valeur.at(0) == '\"' && valeur.at(0) == '\"')
                Compilateur::ParseTree->AddConstant(Constant(nomconst,valeur,Type("chaine")));
            else
                if(valeur.at(0) == '\'' && valeur.at(0) == '\'' && valeur.size() == 3)
                    Compilateur::ParseTree->AddConstant(Constant(nomconst,valeur,Type("caractere")));
                else
                {
                    bool ok;
                    valeur.toInt(&ok);
                    if(ok)
                     {
                        Compilateur::ParseTree->AddConstant(Constant(nomconst,valeur,Type("entier")));
                        continue;
                     }
                    if(valeur.count('.') == 1)
                    {
                        valeur.mid(0,valeur.indexOf('.') - 1).toInt(&ok);
                        if(ok)
                           valeur.mid(valeur.indexOf('.') - 1,-1).toInt(&ok);
                        if(ok)
                        {
                            Compilateur::ParseTree->AddConstant(Constant(nomconst,valeur,Type("reel")));
                            continue;
                        }
                    }
                    emit this->Handle_Error(*ligne,SyntaxicError("Valeur du constante invalide"));

                }

        }
    }
    // ------------------- TYPES      -----------
    QDomElement typesroot = root.firstChildElement("types");
    if(typesroot.hasChildNodes())
            {
                *ligne += 1;
                for(int i = 0; i < typesroot.childNodes().size();i++)
                {
                    *ligne += 1;
                    QDomElement elmtype = typesroot.childNodes().at(i).toElement();
                    try
                    {
                        QString typeName = elmtype.attribute("name");
                        //LexicalAnalyser::isIdToken(typeName);
                        if(elmtype.tagName() == "tab")
                        {
                            bool ok;
                            int size = elmtype.attribute("taille").toInt(&ok);
                            if(!ok || size <= 0)
                                throw SyntaxicError("Taille du tableau invalide");
                            if(elmtype.attribute("contenu").isEmpty())
                                throw SyntaxicError("Type du contenu du tableau invalide");
                            Type contenttype = scope->getType(elmtype.attribute("contenu"));
                            //scope->AddType(Array(typeName,contenttype,size));
                        }
                        else
                            if(elmtype.tagName() == "mat")
                            {
                                bool okL,okC;
                                int size_L = elmtype.attribute("lignes").toInt(&okL);
                                int size_C = elmtype.attribute("colonnes").toInt(&okC);
                                if(!okL || size_L <= 0)
                                    throw SyntaxicError("Nombre des lignes du matrice invalide");
                                if(!okC || size_C <= 0)
                                    throw SyntaxicError("Nombre des colonnes du matrice invalide");
                                if(elmtype.attribute("contenu").isEmpty())
                                    throw SyntaxicError("Type du contenu du tableau invalide");
                                Type contenttype = scope->getType(elmtype.attribute("contenu"));
                               //scope->AddType(MatrixType(typeName,size_C,size_L,contenttype));
                            }
                            else
                                if(elmtype.tagName() == "enreg")
                                {
                                    if(elmtype.hasChildNodes())
                                    {
                                        ligne++;
                                        QDomNodeList listFields = elmtype.elementsByTagName("champ");
                                        QMap<QString,FieldRecord> * mapfields  = new QMap<QString,FieldRecord>();
                                        for(int i = 0; i < listFields.size();i++)
                                        {
                                            QDomElement fieldelm = listFields.at(i).toElement();
                                            QString fieldName = fieldelm.attribute("name");
                                            QString typestring = fieldelm.attribute("type");
                                            if(typestring.isEmpty())
                                                throw SyntaxicError("Type du champinvalide");
                                            //try
                                            {
                                                //LexicalAnalyser::isIdToken(fieldName);
                                            }
                                            // catch lexical error
                                            TypeOfContaint typefield = scope->getTypeContaint(typestring);
                                            FieldRecord field;
                                            field.nom = fieldName;
                                            field.type = typefield;
                                            if(mapfields->contains(fieldName))
                                                throw SyntaxicError("Chmap exist deja essayez d'autre");
                                            mapfields->insert(fieldName,field);
                                        }
                                        RecordType record(typeName);
                                        record.setFields(mapfields);
                                        scope->AddType(&record);
                                    }else
                                    ligne++;
                                }else
                                    if(elmtype.tagName() == "fichier")
                                    {

                                        QString contentTypestring = elmtype.attribute("contenu");
                                        if(contentTypestring.isEmpty())
                                            throw SyntaxicError("Type du contenu du fichier invalide");
                                        //LexicalAnalyser::isIdToken(typeName);
                                        Type typecontent = scope->getType(contentTypestring);

                                        //scope->AddType(FileType(typeName,typecontent));
                                    }
                                    else
                                        qDebug()<<"Type inconnu tag name";

                    }
                    catch(SyntaxicError e)
                    {
                        emit this->Handle_Error(*ligne,e);
                    }
                }
            }
    // ------------------- VARIABLES  -----------
    QDomElement rootvariables = root.firstChildElement("variables");
    if(rootvariables.hasChildNodes())
            {
                QDomNodeList listVars = rootvariables.elementsByTagName("var");
                ligne += 1;
                for(int i = 0; i < listVars.size();i++)
                {
                    ligne += 1;
                    QDomElement elmvar = listVars.at(i).toElement();
                    QString varname = elmvar.attribute("name");
                    QString stringtype = elmvar.attribute("type");
                    // try
                    {
                         //LexicalAnalyser::isIdToken(varname);
                    }
                    // catch lexicical error
                    TypeOfContaint typevar =  scope->getTypeContaint(stringtype);
                    Variable  * v = new Variable(varname,typevar);
                    scope->AddVariable(*v);
                }
            }

}

void SyntaxicAnalyser::ScaneXMLStatment(QDomElement xmlStatment, Statment *statment, int *ligne)
{
    int indexStatment = xmlStatment.attribute("index").toInt();
    *ligne++;
    switch (indexStatment) {

    case XML_ASSIGN :{statment = new Statment();}break;
    case XML_READ   :{statment = new Statment();}break;
    case XML_WRITE  :{statment = new Statment();}break;
    case XML_IF     :{statment = new Statment();}break;
    case XML_ELSE   :{statment = new Statment();}break;
    case XML_SWITCH :{statment = new Statment();}break;
    case XML_CASE   :{statment = new Statment();}break;
    case XML_FOR    :{statment = new Statment();}break;
    case XML_WHILE  :{statment = new Statment();}break;
    case XML_REPEATE:{statment = new Statment();}break;
    case XML_UNTIL  :{statment = new Statment();}break;
    case XML_CALL   :{statment = new Statment();}break;
    case XML_RETURN :{statment = new Statment();}break;
    case XML_COMMENT:{statment = new Statment();}break;
    case XML_END    :{statment = new Statment();}break;

    default:
            qDebug()<< "NO XML STATMENT BEHAVIOR WITH INDEX = " << indexStatment;
        break;
    }
    if(xmlStatment.hasChildNodes())
    {
        QDomNodeList xmlStatments = xmlStatment.elementsByTagName("item");
        for(int i = 0; i < xmlStatments.size();i++)
        {
            QDomElement xmlitem = xmlStatments.at(i).toElement();
            Statment * child_statment ;
            ScaneXMLStatment(xmlitem,child_statment,ligne);
            statment->addChildStatment(child_statment);
        }
    }
}

