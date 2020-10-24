#include "syntaxicanalyser.h"

Constant *c = NULL;
Function *f = NULL;
Procedure*p = NULL;
std::string id_type = "",containttype = "";
RecordType * RDT;
bool signe = false;
std::string id_var = "",typeVar = "";
std::string id_Field = "",typeField = "";
std::string id_fct = "",id_proc = "",returntype = "";
std::string id_compteur = "",vi_pour = "",vf_pour = "";

MainScope *Compilateur::ParseTree = new MainScope();
std::string toUpper(std::string str)
{
    return QString::fromStdString(str).toUpper().toStdString();
}

SyntaxicAnalyser::SyntaxicAnalyser(QObject *parent) :
    QObject(parent)
{
    ExtentionsFilesNames = new QStringList();
    AnalyseMemory = new QList<Token*>();
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
                            throw SyntaxicError(lex->currentLine(),lex->currentLine(),"Mot cle 'Algorithme' Attendu mais le mot '" + QString::fromStdString(t->Value()) + "' trouve " );
                        else
                        {
                            IN_Algorithme = false;
                            IN_id_program = true;
                        }
                    }
                }
                else
                 {
                     if(t->Nature() != ID )
                          throw SyntaxicError(lex->currentLine(),lex->currentLine(),"Identifateur du programme est incorrecte " );
                      else
                      {
                          Compilateur::ParseTree->setName(QString::fromStdString(t->Value()));
                          IN_id_program = false;
                          IN_Id_Algo    = false;
                          IN_Directives = true;
                          IN_Extention  = true;

                      }
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
                        throw SyntaxicError(lex->currentLine(),lex->currentColumn()," invalide nom du fichier d'extention ");
                    else
                    {
                        // TRaitement include ( t->Value());
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
                             throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"indication ambigue par le mot suivant : " + QString::fromStdString(t->Value()));
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
                                    throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Declaration imprique des sous programmes interdit ");
                                else
                                {
                                    IN_ListConsts = IN_Listtypes = IN_listVars = false;
                                    IN_HeaderProgram = false;
                                    IN_Fct = true;
                                    IN_id_fct = true;
                                }
                            }
                        else
                             if(toUpper(t->Value()) == PRocedure)
                            {
                                 if(IN_Proc || IN_Fct)
                                     throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Declaration imprique des sous programmes interdit ");
                                 else
                                 {
                                     IN_ListConsts = IN_Listtypes = IN_listVars = false;
                                     IN_HeaderProgram = false;
                                     IN_Proc   = true;
                                     IN_IdProc = true;
                                 }

                            }
                        else
                            if(toUpper(t->Value()) == Debut)
                            {
                                 IN_ListConsts = IN_Listtypes = IN_listVars = false;
                                 IN_HeaderProgram = false; // FERMER LE HEADER DU PROGRAMME PUIS ALLER VERS LE DEBUT
                                 IN_Debut = true;
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
                                    throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"indication ambigue par le mot suivant : " + QString::fromStdString(t->Value()));
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
                                        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Nom du contante incorrecte");
                                    else
                                    {
                                        c = new Constant(QString::fromStdString( t->Value()));
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
                                    throw SyntaxicError(lex->currentLine(),"Erreur du synatax '=' attendu  ");
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
                                                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Signe incompatible avec le type du valeur ");
                                            else
                                            {
                                                c->setValue(QString::fromStdString( t->Value()));
                                                try
                                                {
                                                    Compilateur::ParseTree->AddConstant(*c);
                                                }catch(QString error)
                                                {
                                                    throw SyntaxicError(lex->currentLine(),0,error);
                                                }

                                                c = NULL;
                                                signe = false;
                                                IN_ConstValue = false;
                                                IN_Constantes = false;
                                            }

                                        }
                                        else
                                            throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Valuer du constantes incorrecte ");
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
                                        id_type = t->Value();
                                        IN_Id_Type = false;
                                        IN_OpertatorType = true;
                                    }
                                    else
                                        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"identificateur du type invalide ");
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
                                        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle '=' de deffinition du type est attendu");
                                }
                                else
                                {
                                    if(!IN_Enreg && !IN_Tab && !IN_Mat && !IN_Fich)
                                      {
                                          if(t->Nature() != ID)
                                                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Indicateur du type incorrecte");
                                          else
                                          if(toUpper(t->Value()) == Enregistrement)
                                          {
                                                IN_Enreg = true;
                                                IN_ID_Field = true;
                                                IN_listFields = true;
                                                RDT = new RecordType();
                                          }
                                          else
                                          if(toUpper(t->Value()) == Tableau)
                                          {
                                                IN_Tab = true;
                                                IN_LI = true;
                                          }
                                          else
                                          if(toUpper(t->Value()) == Ficheir)
                                          {
                                                IN_Fich = true;
                                                IN_DE_Key = true;
                                          }else // ici
                                                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Indicateur du type inconnu '" + QString::fromStdString(t->Value()) + "'");
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
                                                                if(toUpper(t->Value()) == FIN)
                                                                {
                                                                    IN_listFields = false;
                                                                    IN_End = true;
                                                                }
                                                                else
                                                                {
                                                                    id_Field = t->Value();
                                                                    IN_ID_Field = false;
                                                                    IN_AssignType = true;
                                                                }
                                                            }
                                                            else
                                                                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"identificateur du champ incorrecte ");
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
                                                                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"mot cle ':' de attendu ");
                                                        }
                                                        else
                                                        {
                                                            if(t->Nature() == LocationSpecifier)
                                                                typeField.append("@");
                                                            else
                                                                if(t->Nature() == ID)
                                                                {
                                                                    typeField.append(t->Value());
                                                                    try{
                                                                        FieldRecord * field = new FieldRecord();
                                                                        field->nom  = QString::fromStdString(id_Field).toUpper();
                                                                        field->type = Compilateur::ParseTree->getType(QString::fromStdString(typeField).toUpper());
                                                                        RDT->AddField(*field);
                                                                        delete field;
                                                                        id_Field = typeField = "";
                                                                        IN_ID_Field = true;
                                                                    }catch(QString error)
                                                                    {
                                                                        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),error);
                                                                    }
                                                                    IN_typeOfField = false;
                                                                }
                                                                else
                                                                    throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Type du champ incorrecte ");

                                                        }
                                                    }
                                                    else // IN END RECORD
                                                    {
                                                        IN_End  = false;
                                                        IN_Enreg = false;
                                                        IN_Types = false;
                                                        IN_DefType = false;
                                                        RDT->setName(QString::fromStdString(id_type));
                                                        Compilateur::ParseTree->AddType(*RDT);
                                                        RDT = NULL;
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
                                                                 throw SyntaxicError(lex->currentLine(),lex->currentColumn()," Mot cle '[' attendu ");

                                                        }
                                                        else
                                                        if(IN_InitSizeT)
                                                        {
                                                            if(t->Nature() == NUMBER)
                                                            {
                                                                IN_InitSizeT = false;
                                                                IN_Punctiation = true;
                                                            }else
                                                                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Borne inferieur du tableux attendu ");
                                                        }
                                                        else
                                                        if(IN_Punctiation)
                                                        {
                                                            if(t->Nature() == Punctuation && t->Value() == "..")
                                                            {
                                                                IN_Punctiation = false;
                                                                IN_size_c = true;
                                                            }else
                                                                throw SyntaxicError(lex->currentLine(),lex->currentColumn()," Mot clé '..' attendu ");
                                                        }
                                                        else
                                                        if(IN_size_c)
                                                        {
                                                            size_c = QString::fromStdString(t->Value()).toInt();
                                                            if(t->Nature() == NUMBER)
                                                            {
                                                                IN_size_c = false;
                                                                IN_RI = true;
                                                            }else
                                                                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Borne supperieur du tableux attendu ");
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
                                                             if(t->Nature() == Punctuation && t->Value() == ",")
                                                             {
                                                                 IN_Tab = false;
                                                                 IN_ContaintType = false;
                                                                 IN_Mat = true;
                                                                 IN_InitSizeT = true;
                                                             }
                                                            else
                                                                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle ']' attendu");
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
                                                                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle 'DE' attendu");
                                                        }else
                                                        {
                                                            if(t->Nature() == LocationSpecifier)
                                                                containttype.append("@");
                                                            else
                                                            if(t->Nature() == ID)
                                                            {
                                                                try {
                                                                 Array * T = new Array(QString::fromStdString( id_type ) ,QString::fromStdString(containttype.append(t->Value())),size_c);
                                                                 Compilateur::ParseTree->AddType(*T);
                                                                 delete T;
                                                                 size_c = 0;
                                                                }catch(QString error)
                                                                {
                                                                    throw SyntaxicError(lex->currentLine(),lex->currentColumn(),error);
                                                                }

                                                                IN_Tab = false;
                                                                IN_ContaintType = false;
                                                                IN_Types = false;
                                                                IN_DefType = false;
                                                            }else
                                                                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Type de contenu du Tableau incorrecte ");

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
                                                            throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Borne inferieur du Matrice attendu ");
                                                    }
                                                    else
                                                    if(IN_Punctiation)
                                                    {
                                                        if(t->Nature() == Punctuation && t->Value() == "..")
                                                        {
                                                            IN_Punctiation = false;
                                                            IN_size_l = true;
                                                        }else
                                                            throw SyntaxicError(lex->currentLine(),lex->currentColumn()," Mot clé '..' attendu ");
                                                    }
                                                    else
                                                    if(IN_size_l)
                                                    {
                                                        size_l = QString::fromStdString(t->Value()).toInt();
                                                        if(t->Nature() == NUMBER)
                                                        {
                                                            IN_size_l = false;
                                                            IN_RI = true;
                                                        }else
                                                            throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Borne inferieur du Matrice attendu ");
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
                                                            throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle ']' attendu");
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
                                                            throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle 'DE' attendu");
                                                    }else
                                                    {
                                                        if(t->Nature() == LocationSpecifier)
                                                            containttype.append("@");
                                                        else
                                                        if(t->Nature() == ID)
                                                        {
                                                            try {
                                                             MatrixType * T = new MatrixType(QString::fromStdString( id_type ) ,size_c,size_l,QString::fromStdString(containttype.append(t->Value())));
                                                             Compilateur::ParseTree->AddType(*T);
                                                             delete T;
                                                             size_c = 0;
                                                             size_l = 0;
                                                            }catch(QString error)
                                                            {
                                                                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),error);
                                                            }
                                                            IN_Types = false;
                                                            IN_Mat = false;
                                                            IN_ContaintType = false;
                                                            IN_DefType = false;
                                                        }else
                                                            throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Type de contenu du Matrice incorrecte ");
                                                    }
                                                }
                                            }
                                            else
                                            if(IN_Fich)
                                            {
                                                 Fich:{
                                                       //qDebug()<< "fich" << QString::fromStdString(t->Value())<<IN_DE_Key<<IN_ContaintType;
                                                        if(IN_DE_Key)
                                                        {
                                                            if(t->Nature() == ID && toUpper(t->Value()) == "DE")
                                                            {
                                                                IN_DE_Key = false;
                                                                IN_ContaintType = true;
                                                                containttype = "";
                                                            }
                                                            else
                                                                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle 'De' attendu");
                                                        }
                                                        else
                                                        {
                                                            IN_ContaintType = true;
                                                            if(t->Nature() == LocationSpecifier)
                                                                containttype.append("@");
                                                            else
                                                            if(t->Nature() == ID)
                                                            {
                                                                try {
                                                                 FileType * T = new FileType(QString::fromStdString( id_type ) ,QString::fromStdString(containttype.append(t->Value())));
                                                                 Compilateur::ParseTree->AddType(*T);
                                                                 delete T;
                                                                }catch(QString error)
                                                                {
                                                                    throw SyntaxicError(lex->currentLine(),lex->currentColumn(),error);
                                                                }

                                                                IN_Fich = false;
                                                                IN_ContaintType = false;
                                                                IN_Types = false;
                                                                IN_DefType = false;

                                                            }
                                                            else
                                                                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Type de contenu du fichier incorrecte ");

                                                        }

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
                                    throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Identificateur du variable incorrecte ");
                                else
                                {
                                    IN_Id_Var = false;
                                    IN_AssignType = true;
                                    id_var = t->Value();
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
                                    throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot clé ':' attendu mais '" + QString::fromStdString(t->Value()) + "' trouvé ");
                            }
                            else
                            {
                                if(t->Nature() == LocationSpecifier)
                                    id_var.append("@");
                                else
                                    if(t->Nature() == ID)
                                    {
                                        typeVar.append(t->Value());
                                        try{
                                            Variable * v = new Variable(QString::fromStdString(id_var),QString::fromStdString(typeVar));
                                            Compilateur::ParseTree->AddVariable(*v);
                                            typeVar = id_var = "";
                                        }catch(QString error)
                                        {
                                            throw SyntaxicError(lex->currentLine(),lex->currentColumn(),error);
                                        }
                                        IN_TypeOfVar = false;
                                        IN_Variables = false;
                                    }
                                    else
                                        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Type du variable incorrecte ");

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
                    qDebug()<< "In debut fonction  " << QString::fromStdString(t->Value());
                    Statment * debutFct = new Statment();
                    //Instructions(debutFct,lex);
                    IN_Fct = false;
                    IN_Debut = false;
                    IN_HeaderProgram = true;
                }
                else
                if(IN_Proc)
                {
                    qDebug()<< "In debut Procedure " << QString::fromStdString(t->Value());
                    Statment * debutProc = new Statment();
                    IN_Proc = false;
                    IN_Debut = false;
                    IN_HeaderProgram = true;
                    //Instructions(new Function(),lex,debutProc);
                }
                else
                {
                    // inclure les fonctions et procecures ici
                    qDebug()<< "In debut Algorithme " << QString::fromStdString(t->Value());
                }
                if(toUpper(t->Value()) == FIN)
                {
                    IN_Debut = false;
                }
                 // DebutAlgo

            }
            else
            if(IN_Fct)
            {
                //qDebug()<< "In Fonction" << QString::fromStdString(t->Value()) << IN_id_fct << IN_Lp << IN_listArgs <<  IN_Rp << IN_AssignType;

                if(IN_id_fct)
                {
                    if(t->Nature() != ID)
                        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"identificateur du fonction incorrecte ");
                    else
                    {
                        id_fct = toUpper(t->Value());
                        IN_id_fct = false;
                        IN_Lp  = true;
                    }
                }
                else
                if(IN_Lp)
                {
                    if(t->Nature() != Lp)
                        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle ' ( ' attendu ");
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
                    listArgs:{
                        if(IN_ES)
                        {
                            if(toUpper(t->Value()) == "DON" || toUpper(t->Value()) == "RES" || toUpper(t->Value()) == " DONRES" || toUpper(t->Value()) == "DON_RES")
                            {
                                if(IN_Fct)
                                {
                                    if(toUpper(t->Value()) != "DON")
                                        throw SyntaxicError(lex->currentLine(),lex->currentColumn()," Mode du passage interdit ");
                                    else
                                    {
                                       // TRaitment pour fonction
                                    }
                                }else
                                {
                                    // TRaitment pour procedure
                                }
                                IN_ES = false;
                                IN_IdArg = true;

                            }
                            else
                            {
                                IN_ES = false;
                                IN_IdArg = true;
                                goto listArgs;
                            }
                        }
                        else
                        if(IN_IdArg)
                        {
                            if(t->Nature() != ID)
                                throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Identificateur d'argument incorrecte ");
                            else
                            {
                                IN_IdArg = false;
                                IN_AssignType = true;
                            }
                        }
                        else
                         if(IN_AssignType)
                         {
                             if(t->Nature() != AssignType)
                                 throw SyntaxicError(lex->currentLine(),lex->currentColumn()," mot cle ':' attendu  ");
                             else
                             {
                                 // traitement
                                 IN_AssignType = false;
                                 IN_typeOfArg = true;
                             }
                         }
                        else
                         if(IN_typeOfArg)
                         {
                            if(t->Nature() == LocationSpecifier)
                            {
                                // typeofarg.append("@");
                            }
                            else
                            {
                                // traiatment
                                IN_typeOfArg = false;
                            }
                         }
                        else
                         {
                             if(t->Value() == ",")
                             {
                                 IN_ES = true;
                             }
                             else
                             {
                                 IN_listArgs = false;
                                 IN_IdArg = false;
                                 IN_Rp = true;
                                 goto ReloadAll;
                             }

                         }

                    }//listArgs
                }
                else
                if(IN_Rp)
                {
                    if(t->Nature() != Rp)
                        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle ')' attendu ");
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
                        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle ':' attendu ");
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
                        returntype.append("@");
                    else
                    if(t->Nature() == ID)
                    {
                        returntype.append(t->Value());
                        IN_returnType = false;
                        IN_HeaderProgram = true;
                    }
                    else
                        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"type de retour de fonction incorrecte ");
                }else
                {
                    IN_HeaderProgram = true;
                    // il va retourner vers le IN_HeaderProgeram Jusqu'a ce dernier recoive la valeur false pour terminer celui ;

                    if(toUpper(t->Value()) != id_fct && t->Value() != ".")
                        goto ReloadAll;
                }

            }
            else
            if(IN_Proc)
            {
                //qDebug()<< "In Procedure" << QString::fromStdString(t->Value()) << IN_IdProc << IN_Lp << IN_listArgs <<  IN_Rp;

                if(IN_IdProc)
                {
                    if(t->Nature() != ID)
                        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"identificateur du procedure incorrecte ");
                    else
                    {
                        id_proc = toUpper(t->Value());
                        IN_IdProc = false;
                        IN_Lp  = true;
                    }
                }
                else
                if(IN_Lp)
                {
                    if(t->Nature() != Lp)
                        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle ' ( ' attendu ");
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
                        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle ')' attendu ");
                    else
                    {
                        IN_Rp = false;
                        IN_HeaderProgram = true;
                    }
                }
                else
                {
                    IN_HeaderProgram = true;
                    IN_ListConsts = IN_Listtypes = IN_listVars = false;

                    if(toUpper(t->Value()) != id_proc && t->Value() != ".")
                        goto ReloadAll;
                }
            }
            else
            {
                if(IN_Fct)
                {
                    qDebug()<< "In END fonction  ";
                    IN_Fct = false;//ICI
                }
                else
                if(IN_Proc)
                {
                    qDebug()<< "In END Procedure ";
                    IN_Proc = false;//ICI
                }
                else
                {
                    // include les fonctions et procecures ici
                    qDebug()<<QString::fromStdString(t->Value()) << "In END Algorithme ";
                }
                //return ;
            }
        }
        t = lex->NextToken();
    }
}

void SyntaxicAnalyser::Instructions(Statment * parentstatment,LexicalAnalyser * lex)
{       
    bool IN_Instrictions = false;
    bool IN_Si         = false;

    bool IN_Pour       = false;
    bool IN_Compteur   = false;
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
                    IN_Vi = true;
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
                if(toUpper(t->Value()) == "FIN")
                {
                    return;
                }
                else
                {
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
                       throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Instruction 'SI NON' male utilisé ");
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
               if(IN_Instrictions)
               {
                   // + CREATION INSTRUCTION SI ... ALORS
                   Statment * Si_Statment = new Statment();
                   parentstatment->addChildStatment(Si_Statment);
                   Instructions(Si_Statment,lex);

                   // - CREATION INSTRUCTION SI ... ALORS
               }
               else
               if(toUpper(t->Value()) == Si)
               {
                   IN_Si = false;
               }
               else
                  throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle 'Fin Si' attendu ");
            }
            else
            if(IN_Pour)
            {
               if(IN_Compteur)
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
                       IN_Compteur = false;
                       IN_TO_FOR = true;
                   }
                   else
                       throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"identificateur du compteur du boucle POUR incorrecte ");

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
                        throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle 'FAIRE ' Attendu ");

                }
                else
                if(toUpper(t->Value()) == TanteQue)
                {
                    IN_TanteQue = false;
                }
                else
                    throw SyntaxicError(lex->currentLine(),lex->currentColumn(),"Mot cle 'FIN TANTEQUE ' Attendu ");

            }
            else
            if (IN_Repeter)
            {
                Statment * repeat = new Statment();
                Instructions(repeat,lex);
                // expression
                Expression(repeat,lex);
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

}

void SyntaxicAnalyser::Expression(Statment *statment, LexicalAnalyser *lex)
{
    Token * t = NULL;
    while ((t = lex->NextToken())) {

    }
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
            Type typretour = Compilateur::ParseTree->getType(elmfct.attribute("type"));
            // try
            {
                //LexicalAnalyser::isIdToken(fctname);
            }
            // catching lexical error
            Function fct(fctname,typretour);
            fct.extandsTypes(Compilateur::ParseTree->getTypes());

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

                Type typearg = Compilateur::ParseTree->getType(stringtypearg);

                Argment arg(namearg,typearg,io);
                try{
                    fct.addArg(arg);
                }catch(SyntaxicError e)
                {
                    this->Handle_Error(ligne,e);
                }
            }
            Compilateur::ParseTree->AddSubProgram(fct);
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
            procedure.extandsTypes(Compilateur::ParseTree->getTypes());

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

                Type typearg = Compilateur::ParseTree->getType(stringtypearg);

                Argment arg(namearg,typearg,io);
                try{
                    procedure.addArg(arg);
                }catch(SyntaxicError e)
                {
                    this->Handle_Error(ligne,e);
                }
            }
            Compilateur::ParseTree->AddSubProgram(procedure);
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
                            scope->AddType(Array(typeName,contenttype,size));
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
                               scope->AddType(MatrixType(typeName,size_C,size_L,contenttype));
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
                                            Type typefield = scope->getType(typestring);
                                            FieldRecord field;
                                            field.nom = fieldName;
                                            field.type = typefield;
                                            if(mapfields->contains(fieldName))
                                                throw SyntaxicError("Chmap exist deja essayez d'autre");
                                            mapfields->insert(fieldName,field);
                                        }
                                        RecordType record(typeName);
                                        record.setFields(mapfields);
                                        scope->AddType(record);
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

                                        scope->AddType(FileType(typeName,typecontent));
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
                    Type typevar =  scope->getType(stringtype);

                    scope->AddVariable(Variable(varname,typevar));
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

/*
 *     // Algorithme < Id_program >
    Token * t = lexicalAnalyser->NextToken();
    if(!t)
        throw SyntaxicError();
    else
        {
            t = lexicalAnalyser->NextToken();
            if(!t)
                throw SyntaxicError();
            else
            {
                if(t->Nature() != ID)
                    throw SyntaxicError();
                else
                {
                    MainScope * mainscope = new MainScope(t->Value());
                    t = lexicalAnalyser->NextToken();
                    if(!t)
                        throw SyntaxicError();
                    else
                    {

                    }
                }
            }
        }
*/

