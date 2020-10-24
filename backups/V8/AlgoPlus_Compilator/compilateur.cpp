#include "compilateur.h"

Compilateur::Compilateur(QObject *parent) :
    QObject(parent)
{
    //liste_motsJS<<"var"<<"function"<<"this"<<"return"<<"String"<<"Object"<<"Array"<<"Date"<<"Math";
    this->ParseTree = new MainScope();
    //syntaxicAnalyser = new SyntaxicAnalyser(this);
    //connect(this->syntaxicAnalyser,SIGNAL(Handle_Error(int,SyntaxicError)),this,SLOT(emitError(CompilationError)));
    //connect(this->syntaxicAnalyser,SIGNAL(Handle_Warning(int,QString)),this,SLOT(emitWarning(Warning)));
}

void Compilateur::Compiler(const QDomDocument documentAlgorithme)
{
    this->documentAlgorithme = documentAlgorithme;
    Compiler();
}

void Compilateur::Compiler()
{

}

void Compilateur::Clear()
{
    this->listErrors.clear();
    this->listWarning.clear();

}

void Compilateur::emitError(const CompilationError error)
{
    this->listErrors<<error;
    emit this->hasError(error);
}

void Compilateur::emitWarning(const Warning warning)
{
    this->listWarning<<warning;
    emit this->hasWarning(warning);
}
/*

void Compilateur::compiler(QDomDocument document)
{
    documentAlgorithme  = document;
    contextProgramme_Principale = new Context_Memoire(this);
    int ligne = 1;
    outPutProgram.clear();
    liste_erreur.clear();

    sortie->insertPlainText("*** Compilation commencé ***\n");

    QDomElement racineAlgo = document.documentElement();
    /// ------------------ TRAITEMENT CONSTANTES ALGO + ----------------------
    QDomElement racineConstantes = racineAlgo.firstChildElement("constantes");
    if(racineConstantes.hasChildNodes())
    {
        ligne++;
        for(int i = 0; i < racineConstantes.elementsByTagName("const").size();i++)
        {
            ligne++;
            QDomElement elmconst = racineConstantes.elementsByTagName("const").at(i).toElement();
            QString nomconst = elmconst.attribute("name");
            QString valeurConst = elmconst.attribute("valeur");
            try{


            }catch(QString error)
            {
                liste_erreur<< "Ligne : " + QString::number(ligne) + " " + error;
            }
        }
    }

    /// ------------------ TRAITEMENT TYPES ALGO + ---------------------------
    QDomElement racineTypes = racineAlgo.firstChildElement("types");
    if(racineTypes.hasChildNodes())
    {
        ligne++;
        for(int i = 0; i < racineTypes.childNodes().size();i++)
        {
            ligne++;
            QDomElement elmType = racineTypes.childNodes().at(i).toElement();
            if(elmType.tagName() == "tab")
                outPutProgram += Compiler_Tableau(elmType,ligne);
            else
                if(elmType.tagName() == "mat")
                    outPutProgram += Compiler_Matrice(elmType,ligne);
                    else
                        if(elmType.tagName() == "enreg")
                            outPutProgram += Compiler_Enregistrement(elmType,&ligne);
                            else
                                if(elmType.tagName() == "fich")
                                    outPutProgram += Compiler_Fichier(elmType,ligne);
                                    else
                                        {
                                           qDebug()<<"Compilateur -> genre de type indeffint : " + elmType.tagName();
                                        }

        }
    }

    /// ------------------ TRAITEMENT VARIABLES PROGRAMME PRINCIPALE ---------
    QDomElement racineVariables = racineAlgo.firstChildElement("variables");
    if(racineVariables.hasChildNodes())
    {
        ligne++;
        QStringList listevar;
        for(int i = 0; i < racineVariables.elementsByTagName("var").size();i++)
        {
            ligne++;
            QDomElement elmvar = racineVariables.elementsByTagName("var").at(i).toElement();

            outPutProgram += Compiler_Variable(elmvar,ligne,&listevar,contextProgramme_Principale);
        }
    }
    /// ------------------ TRAITEMENT FONCTIONS --------------------------------
    QDomElement racineFonctions = racineAlgo.firstChildElement("fonctions");
    if(racineFonctions.hasChildNodes())
    {
        for(int i = 0; i < racineFonctions.elementsByTagName("fct").size();i++)
        {
            ligne++;
            QDomElement fonction = racineFonctions.elementsByTagName("fct").at(i).toElement();
            outPutProgram += Compiler_Fonction(fonction,&ligne);
        }
    }
    /// ------------------ TRAITEMENT PROCEDURES --------------------------------
    QDomElement racineProcedures = racineAlgo.firstChildElement("procedures");
    if(racineProcedures.hasChildNodes())
    {
        for(int i = 0; i < racineProcedures.elementsByTagName("proc").size();i++)
        {
            ligne++;
            QDomElement procedure = racineProcedures.elementsByTagName("proc").at(i).toElement();
            outPutProgram += Compiler_Procedure(procedure,&ligne);
        }
    }
    / *qDebug()<<"*** context memoire programme proncipale **************************";
    //contextProgramme_Principale->debugger();
    qDebug()<<"*******************************************************************";* /
    /// ------------------- TRAITEMENT DEBUT ALGORITHME --------------------------

    QDomElement DebutAlgo = racineAlgo.firstChildElement("Debut").toElement();
    ligne++;
    if(DebutAlgo.hasChildNodes())
        outPutProgram += Compiler_DebutProgramme(DebutAlgo.elementsByTagName("item"),contextProgramme_Principale,&ligne);
    ligne++;
    /// ++++++++++++++++++++++++++++++++ FIN +++++++++++++++++++++++++++++++++++++++
    if(liste_erreur.isEmpty())
        sortie->insertPlainText("*** Compilation terminé ***");
    else
    {
        for(int i = 0; i < liste_erreur.size();i++)
            sortie->insertPlainText(liste_erreur.at(i) + "\n");
        sortie->insertPlainText("*** Compilation terminé avec un suite des erreurs ***");
    }
}

QString Compilateur::Pas_espace(QString chaine)
{
    if(chaine.isEmpty())
        return "";
    while (chaine.at(0).isSpace()) {
        chaine.remove(0,1);
    }
    while (chaine.at(chaine.size()-1).isSpace()) {
        chaine.remove(chaine.size()-1,1);
    }
    return chaine;

}

QString Compilateur::Compiler_constante(QDomElement elm_constante,int ligne)
{
    QString nom = Pas_espace(elm_constante.attribute("name"));
    /// ------------------ TRAITEMENT NOM CONSTANTE -------------------------
    if(!nom.isEmpty())
    {
        if(nom.at(0).isLetter())
        {
            for(int i = 1; i < nom.size();i++)
            {
                if(nom.at(i).isSpace())
                    liste_erreur<< "ligne : " + QString::number(ligne) + " -> Nom de constante contient un espace";
                else
                    if(!nom.at(i).isLetterOrNumber() && nom.at(i) != '_')
                        liste_erreur<<"ligne : " + QString::number(ligne) +  QString("->Nom de constante contient un symbole ").append(nom.at(i));
            }
        }
        else
            liste_erreur<<"ligne : " + QString::number(ligne) + " -> Nom de symbole doit commencé par une lettre";
        if(liste_Constantes.contains(nom))
            liste_erreur<<"ligne : " + QString::number(ligne) + " -> Constante déja déclarer";

        liste_Constantes<<nom;
    }
    else
        liste_erreur<<"ligne : " + QString::number(ligne) + " -> Nom de constante indeffint";
    if(liste_motsJS.contains(nom))
        liste_erreur<<"ligne : " + QString::number(ligne) + " -> Nom de constante interdit";
    /// ------------------ TRAITEMENT VALEUR CONSTANTE -------------------------
    QString valeur = Pas_espace(elm_constante.attribute("valeur"));

    if(valeur.isEmpty())
    {
        for(int i = 0; i < valeur.size();i++)
            if(!valeur.at(i).isNumber() || valeur.at(i) != '.' || Occurence('.',valeur) > 1)
                liste_erreur<<"ligne : " + QString::number(ligne) + " -> Valeur de constante doit etre un entier ou un reel";
    }
    else
        liste_erreur<<"ligne : " + QString::number(ligne) + " -> Valeur de constante indeffint";

    return "";
}

QString Compilateur::Compiler_Tableau(QDomElement elmTab, int ligne)
{
    /// ----------------- TRAITEMENT NOM DE TABLEAU --------------------------

    QString nom = Pas_espace(elmTab.attribute("name"));
    QString message_c = Controle_NomType(nom);
    if(!message_c.isEmpty())
        liste_erreur<<"Ligne " + QString::number(ligne) + " -> " + message_c;
    if(!nom.isEmpty())
    {
        liste_Tableaux<<nom;
        liste_types<<nom;
        liste_typesContenu<<nom<<"@" + nom;
    }
    /// ----------------- TRAITEMENT TYPE DE CONTENU -------------------------
    QString type = elmTab.attribute("contenu");
    type = Pas_espace(type);

    if(!liste_typesContenu.contains(type))
        liste_erreur<<"Ligne " + QString::number(ligne) + " -> type de contenu n'est pas declare";
    if(nom == type)
        liste_erreur<<"Ligne " + QString::number(ligne) + " -> déclaration évoque un erreur d'execution";
    /// ---------------- TRAItEMENT NOMBRE DES CASES -------------------------

    QString ch_T = elmTab.attribute("taille");
    ch_T = Pas_espace(ch_T);
    if(ch_T.isEmpty())
        liste_erreur<<"Ligne " + QString::number(ligne) + " -> Taille de tableau est indeffinit";
    if(!estNombre(ch_T))
    {
        if(documentAlgorithme.documentElement().firstChildElement("constantes").hasChildNodes())
        {
            QDomElement racineconstantes = documentAlgorithme.documentElement().firstChildElement("constantes");
            for(int i = 0; i < racineconstantes.childNodes().size();i++)
            {
                QDomElement elmc = racineconstantes.childNodes().at(i).toElement();
                QString nomconst = Pas_espace(elmc.attribute("name"));
                if(!nomconst.isEmpty() && nomconst == ch_T)
                {
                    if(!estNombre(Pas_espace(elmc.attribute("valeur"))))
                        liste_erreur<<"Ligne" + QString::number(ligne) + " -> taille de tableau ne correspand pas à un entier ou à un valeur d'entier";
                    break;
                }
            }
        }
    }
    int taille = ch_T.toInt();

    /// --------------------------- LA CONVERSION CONVENABLE -----------------
    return "";

}

QString Compilateur::Compiler_Matrice(QDomElement elmMat, int ligne)
{
    /// ----------------- TRAITEMENT NOM TYPE --------------------------------
    QString nom = Pas_espace(elmMat.attribute("name"));
    QString message_c = Controle_NomType(nom);
    if(!message_c.isEmpty())
        liste_erreur<< "Ligne " + QString::number(ligne) + " ->" + message_c;
    if(!nom.isEmpty())
    {
        liste_matrices<<nom;
        liste_types<<nom;
        liste_typesContenu<<nom<<"@"+nom;
    }
    /// ----------------- TRAITEMENT TYPE DE CONTENU ------------------------
    QString type = Pas_espace(elmMat.attribute("name"));
    if(!liste_typesContenu.contains(nom))
        liste_erreur<<"Ligne " + QString::number(ligne) + " -> type de contenu n'est pas declare";
    if(nom == type)
        liste_erreur<<"Ligne " + QString::number(ligne) + " -> déclaration évoque un erreur d'execution";
    /// ----------------- TRAITEMENT NOMBRE DES LIGNE -----------------------
    QString ch_ligne = elmMat.attribute("ligne");
    ch_ligne = Pas_espace(ch_ligne);
    if(ch_ligne.isEmpty())
        liste_erreur<<"Ligne " + QString::number(ligne) + " -> nombre des ligne de matrice est indeffinit";
    if(!estNombre(ch_ligne))
    {
        if(documentAlgorithme.documentElement().firstChildElement("constantes").hasChildNodes())
        {
            QDomElement racineconstantes = documentAlgorithme.documentElement().firstChildElement("constantes");
            for(int i = 0; i < racineconstantes.childNodes().size();i++)
            {
                QDomElement elmc = racineconstantes.childNodes().at(i).toElement();
                QString nomconst = Pas_espace(elmc.attribute("name"));
                if(!nomconst.isEmpty() && nomconst == ch_ligne)
                {
                    if(!estNombre(Pas_espace(elmc.attribute("valeur"))))
                        liste_erreur<<"Ligne" + QString::number(ligne) + " -> nombre des ligne de matrice ne correspand pas à un entier ou à un valeur d'entier";
                    break;
                }
            }
        }
    }
    int nbr_ligne = ch_ligne.toInt();
    /// ----------------- TRAITEMENT NOMBRE DES COLONNES ----------------------
            QString ch_colonne = elmMat.attribute("colonne");
            ch_colonne = Pas_espace(ch_colonne);
            if(ch_colonne.isEmpty())
                liste_erreur<<"Ligne " + QString::number(ligne) + " -> nombre des ligne de matrice est indeffinit";
            if(!estNombre(ch_colonne))
            {
                if(documentAlgorithme.documentElement().firstChildElement("constantes").hasChildNodes())
                {
                    QDomElement racineconstantes = documentAlgorithme.documentElement().firstChildElement("constantes");
                    for(int i = 0; i < racineconstantes.childNodes().size();i++)
                    {
                        QDomElement elmc = racineconstantes.childNodes().at(i).toElement();
                        QString nomconst = Pas_espace(elmc.attribute("name"));
                        if(!nomconst.isEmpty() && nomconst == ch_colonne)
                        {
                            if(!estNombre(Pas_espace(elmc.attribute("valeur"))))
                                liste_erreur<<"Ligne" + QString::number(ligne) + "-> nombre des ligne de matrice ne correspand pas à un entier ou à un valeur d'entier";
                            break;
                        }
                    }
                }
            }
     int nbr_colonne = ch_ligne.toInt();
    /// ------------------------ CONVERTIONS ---------------------------------
   return "";

}

QString Compilateur::Compiler_Enregistrement(QDomElement elmEnreg, int *ligne)
{
    QString convertion_enreg = "";
    /// ------------------------ TRAITEMENT NOM TYPE -------------------------
    QString nom = Pas_espace(elmEnreg.attribute("name"));
    QString message_c = Controle_NomType(nom);
    if(!message_c.isEmpty())
        liste_erreur<< "Ligne " + QString::number(*ligne) + " ->" + message_c;
    if(!nom.isEmpty())
    {
        liste_enregs<<nom;
        liste_types<<nom;
        liste_typesContenu<<nom<<"@"+nom;
    }
    /// ------------------------ TRAITEMENT CHAMPS ----------------------------
    if(elmEnreg.hasChildNodes())
    {
        QStringList liste_champs;
        for(int i = 0; i < elmEnreg.elementsByTagName("champ").size();i++)
        {
            *ligne = *ligne + 1;
            QDomElement champ = elmEnreg.elementsByTagName("champ").at(i).toElement();
            convertion_enreg += Compiler_Champ(champ,*ligne,&liste_champs,nom);
        }
    }else
        liste_erreur<<"Ligne " + QString::number(*ligne) + " -> enregistrement vide";
    if(liste_erreur.isEmpty())
        return "";/// con ici;
    else
        return "";
}

QString Compilateur::Compiler_Fichier(QDomElement elmFich, int ligne)
{
    /// ----------------------- TRAITEMENT NOM TYPE ----------------------------
    QString nom = Pas_espace(elmFich.attribute("name"));
    QString message_c = Controle_NomType(nom);
    if(!message_c.isEmpty())
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> " + message_c;
    if(!nom.isEmpty())
    {
        liste_fichiers<<nom;
        liste_types<<nom;
        liste_typesContenu<<nom<<"@"+nom;
    }
    /// ---------------------- TRAITEMENT TYPE ---------------------------------
    QString type = Pas_espace(elmFich.attribute("name"));
    if(!liste_typesContenu.contains(type))
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> type de contenu n'est pas declare";
    if(type == nom)
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> déclaration évoque un erreur d'execution";
    /// -------------------- CONVERTION
    if(liste_erreur.isEmpty())
        return "";/// con ici;
    else
        return "";
}

QString Compilateur::Compiler_Champ(QDomElement champ, int ligne, QStringList *listeChamps,QString nomEnreg)
{
    /// ---------------------- TRAITEMENT NOM CHAMP ------------------------------
    QString nom = Pas_espace(champ.attribute("name"));

    if(!nom.isEmpty())
    {
        if(!nom.at(0).isLetter())
            liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Nom de champ doit commencer par un lettre";
        for(int i = 1; i < nom.size();i++)
            if(!nom.at(i).isLetterOrNumber() && nom.at(i) != '_')
                liste_erreur<<"Ligne : " + QString::number(ligne) + QString(" -> Nom de champ contient un symbole interdit '").append(nom.at(i)) + "'";
    listeChamps->append(nom);
    }else
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Nom de champ indeffinit";

    /// --------------------- TRAITEMENT TYPE -------------------------------------
    QString type = Pas_espace(champ.attribute("type"));
    if(!type.isEmpty())
    {
        if(!liste_typesContenu.contains(type))
            liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Type de champ n'est pas declaré";
        if(!nomEnreg.isEmpty())
            if(nomEnreg == type)
                liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Type de champ évoque un erreur d'excution";
    }
    else
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Type de champ indeffint";

    /// ----------------------- Convertion ----------------------------------------
    if(liste_erreur.isEmpty())
        return "";/// convertion ici;
    else
        return "";
}

QString Compilateur::Compiler_Variable(QDomElement elmvar, int ligne,QStringList *listeVars,Context_Memoire * contextMemoire)
{
    /// ---------- TRAITEMENT NOM VARIABLE --------------------------
    QString nom = Pas_espace(elmvar.attribute("name"));
    if(!nom.isEmpty())
    {
        if(!nom.at(0).isLetter())
            liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Nom de variable doit commencer par une lettre";
        for(int i = 1; i < nom.size();i++)
            if(!nom.at(i).isLetterOrNumber() && nom.at(i) != '_')
                liste_erreur<<"Ligne : " + QString::number(ligne) + " -> " + QString("Nom de variable doit commencer par une lettre").append(nom.at(i)) + "'";
    }else
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Nom de variable indeffinit";
    if(!nom.isEmpty())
    {
        if(liste_motsJS.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Variable interdit";
        if(liste_Constantes.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Variable déja declare comme un constante";
        if(liste_types.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Variable déja declare comme un type";

        if(listeVars->contains(nom))
            liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Variable déja declare";
        listeVars->append(nom);
    }
    /// ---------- TRAITEMENT TYPE VARIABLE --------------------------
    QString type = Pas_espace(elmvar.attribute("type"));
    if(type.isEmpty())
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Type de variable indeffinit";
    if(!liste_typesContenu.contains(type))
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Type de variable n'est pas declare";
    /// *********************  Ajout dans le context memoire ************
    contextMemoire->AjouterVariable(nom,type);
    /// ------------ CONVERSION
    if(liste_erreur.isEmpty())
        return "";/// conv ici
    else
        return "";
}

QString Compilateur::Compiler_Fonction(QDomElement fonction, int *ligne)
{
    QString outputfct = "";
    Context_Memoire * contextMemoireFonction = new Context_Memoire(this);
    /// -------------------- TRAITEMENT NOM DE FONCTION ----------------
    QString nom = Pas_espace(fonction.attribute("name"));

    if(!nom.isEmpty())
    {
        if(!nom.at(0).isLetter())
            liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Nom de fonction doit commencer par une lettre";
        for(int i = 1; i < nom.size();i++)
            if(!nom.at(i).isLetterOrNumber() && nom.at(i) != '_')
                liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> " + QString("Nom de fonction contient un symbole ").append(nom.at(i)) + "'";
    }
    else
        liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Nom de fonction indeffinit";
    if(!nom.isEmpty())
    {
        if(liste_motsJS.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Nom de fonction interdit";
        if(liste_Constantes.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Nom de fonction déja declare comme un constante";
        if(liste_types.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Nom de fonction déja declare comme un type";
        if(liste_variables.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Nom de fonction déja declare comme un variable";
        if(liste_programmes.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Nom de fonction déja declare";

        liste_fonction<<nom;
        liste_programmes<<nom;
    }


    /// ------------------- TRAITEMENT TYPE DE RETOURNE -----------------
    QString type = Pas_espace(fonction.attribute("type"));
    if(!liste_typesContenu.contains(type))
        liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Type de retourne de fonction n'est pas declare";
    /// ------------------- TRAITEMENT PARAMETRES -----------------------
    QDomNodeList listeParas = fonction.elementsByTagName("para");

    if(!listeParas.isEmpty())
    {
        QStringList listeParametres;
        for(int i = 0; i < listeParas.size();i++)
        {
            QDomElement parametre = listeParas.at(i).toElement();
            outputfct += Compiler_Parametre(true,parametre,*ligne,&listeParametres);
        }
    }
    /// ------------------- TRAITEMENT DE VARIABLE LOUVAUX ------------------
    QDomElement racineVariables = fonction.firstChildElement("variables");
    if(racineVariables.hasChildNodes())
    {
        *ligne = *ligne + 1;
        QStringList listeVrasLoc;
        for(int i = 0; i < racineVariables.elementsByTagName("var").size();i++)
        {
            *ligne = *ligne + 1;
            QDomElement variable = racineVariables.elementsByTagName("var").at(i).toElement();
            outputfct += Compiler_Variable(variable,*ligne,&listeVrasLoc,contextMemoireFonction);
        }
    }
    / *qDebug()<<"***context memoire fonction " << fonction.attribute("name") << "****";
    contextMemoireFonction->debugger();
    qDebug()<<"********************************************************************";* /
    /// ------------------ TRAITEMENT DEBUT FONCTION -----------------------
    QDomElement Debutfct = fonction.firstChildElement("Debut");
    *ligne = *ligne + 1;
    if(Debutfct.hasChildNodes())
        outputfct += Compiler_DebutProgramme(Debutfct.elementsByTagName("item"),contextMemoireFonction,ligne);
    *ligne = *ligne + 1;
    /// -------------------- Conversion ----------------------------------
    return outputfct;
}

QString Compilateur::Compiler_Procedure(QDomElement procedure, int *ligne)
{
    QString outputproc = "";
    Context_Memoire * contextMemoireProcedure = new Context_Memoire(this);
    /// -------------------- TRAITEMENT NOM DE FONCTION ----------------
    QString nom = Pas_espace(procedure.attribute("name"));

    if(!nom.isEmpty())
    {
        if(!nom.at(0).isLetter())
            liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Nom de procedure doit commencer par une lettre";
        for(int i = 1; i < nom.size();i++)
            if(!nom.at(i).isLetterOrNumber() && nom.at(i) != '_')
                liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> " + QString("Nom de procedure contient un symbole ").append(nom.at(i)) + "'";
    }
    else
        liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Nom de procedure indeffinit";
    if(!nom.isEmpty())
    {
        if(liste_motsJS.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Nom de procedure interdit";
        if(liste_Constantes.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Nom de procedure déja declare comme un constante";
        if(liste_types.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Nom de procedure déja declare comme un type";
        if(liste_variables.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Nom de procedure déja declare comme un variable";
        if(liste_programmes.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(*ligne) + " -> Nom de procedure déja declare";

        liste_procedures<<nom;
        liste_programmes<<nom;
    }

    /// ------------------- TRAITEMENT PARAMETRES -----------------------
    QDomNodeList listeParas = procedure.elementsByTagName("para");

    if(!listeParas.isEmpty())
    {
        QStringList listeParametres;
        for(int i = 0; i < listeParas.size();i++)
        {
            QDomElement parametre = listeParas.at(i).toElement();
            outputproc += Compiler_Parametre(false,parametre,*ligne,&listeParametres);
        }
    }
    /// ------------------- TRAITEMENT DE VARIABLE LOUVAUX ------------------
    QDomElement racineVariables = procedure.firstChildElement("variables");
    if(racineVariables.hasChildNodes())
    {
        *ligne = *ligne + 1;
        QStringList listeVarsLocs;
        for(int i = 0; i < racineVariables.elementsByTagName("var").size();i++)
        {
            *ligne = *ligne + 1;
            QDomElement variable = racineVariables.elementsByTagName("var").at(i).toElement();
            outputproc += Compiler_Variable(variable,*ligne,&listeVarsLocs,contextMemoireProcedure);
        }
    }
    / * qDebug()<<"***context memoire procedure " << procedure.attribute("name") << "****";
    contextMemoireProcedure->debugger();
    qDebug()<<"********************************************************************";* /
    /// ------------------ TRAITEMENT DEBUT FONCTION -----------------------
    QDomElement DebutProc = procedure.firstChildElement("Debut");
    *ligne = *ligne + 1;
    if(DebutProc.hasChildNodes())
        outputproc += Compiler_DebutProgramme(DebutProc.elementsByTagName("item"),contextMemoireProcedure,ligne);
    *ligne = *ligne + 1;
    /// -------------------- Conversion ----------------------------------
    return outputproc;

}


QString Compilateur::Compiler_Parametre(bool fonction,QDomElement parametre, int ligne,QStringList *listeParametre)
{
    /// ---------------- TRAITEMENT NOM --------------------------------
    QString nom = Pas_espace(parametre.attribute("name"));
    if(!nom.isEmpty())
    {
        if(!nom.at(0).isLetter())
            liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Nom de parametre doit commencer par une lettre";
        for(int i = 1; i < nom.size();i++)
            if(!nom.at(i).isLetterOrNumber() && nom.at(i) != '_')
                liste_erreur<<"Ligne : " + QString::number(ligne) + " -> " + QString("Nom de parametre contient un symbole '").append(nom.at(i)) + "'";
    }else
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Nom de parametre indeffinit";

    if(!nom.isEmpty())
    {
        if(liste_motsJS.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Nom de parametre interdit";
        if(liste_types.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Nom de parametre déja declarer comme un type";
        if(liste_programmes.contains(nom))
            liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Nom de parametre déja declarer comme un nom de programme";
        if(listeParametre->contains(nom))
            liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Nom de parametre déja declarer ";
        listeParametre->append(nom);
    }
    /// --------------- TRAITEMENT TYPE ---------------------------------
    QString type = Pas_espace(parametre.attribute("type"));
    if(!type.isEmpty())
    {
        if(!liste_typesContenu.contains(type))
            liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Type de parametre n'est pas declare";
    }else
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Type de parametre indeffinit";
    /// ------------- TRAITEMENT DE PASSAGE ------------------------------
     if(fonction)
     {
         QString passage = Pas_espace(parametre.attribute("passage"));
         bool ok;
         int p =  passage.toInt(&ok);
         if(ok && !passage.isEmpty())
         {
             if(p)
                 liste_erreur<<"Ligne : " + QString::number(ligne) + " -> passage de passage par adresse à une fonction interdit";
         }else
             liste_erreur<<"Ligne : " + QString::number(ligne) + " -> passage de parametre indeffinit";
     }
     /// ------------- Convertion -------------
     return "";
}


QString Compilateur::Compiler_DebutProgramme(QDomNodeList Instructions, Context_Memoire * ContextMemoireProgramme, int *ligne)
{
    QString script = "";
    for(int i = 0; i < Instructions.size();i++)
    {
        QDomElement instruction = Instructions.at(i).toElement();
        *ligne = *ligne + 1;
        //qDebug()<<"ligne"<<*ligne<<instruction.attribute("index");
        if(instruction.hasChildNodes())
            script += Compiler_DebutProgramme(instruction.elementsByTagName("item"),ContextMemoireProgramme,ligne);
    }
    return script;
}

QString Compilateur::Compiler_Instruction(QDomElement instruction, Context_Memoire* contextMemoire,int ligne)
{
   bool ok;
   int index = instruction.attribute("index").toInt(&ok);
   if(ok)
   {
       switch (index) {
       case -1 :return "do{";break;
       case 0 :return "}";break;
       case 1 :return Compiler_Affectation(instruction,contextMemoire,ligne);break;
       case 2 :return Compiler_Lecture(instruction,contextMemoire,ligne);break;
       case 3 :return Compiler_Ecriture(instruction,contextMemoire,ligne);break;
       case 4 :return "// " + instruction.attribute("com");break;
       case 5 :
               {
                   QString condition_si;// = Compiler_Condition(instruction.attribute("condition"),contextMemoire,ligne);
                   if(condition_si.isEmpty())
                       return "";
                   else
                       return "";
               }break;
       case 6 :return ""; break;
       case 7 :return "";break; // C ' est pour selon(...) Faire
       case 8 :return ""; break;// C ' est pour une chois  : ;
       case 9 :return Compiler_Pour_Faire(instruction,contextMemoire,ligne);break;
       case 10:{
               QString condition_Tanteque;// = Compiler_Condition(instruction.attribute("condition"),contextMemoire,ligne);
               if(condition_Tanteque.isEmpty())
                   return "";
               else
                   return "";
               } break;
       case 11:{
           QString condition_jusqua;// = Compiler_Condition(instruction.attribute("condition"),contextMemoire,ligne);
           if(condition_jusqua.isEmpty())
               return "";
           else
               return "";
           } break;
       case 12:return Compiler_Appelle_Procedure(instruction,contextMemoire,ligne);break;
       case 13:
           {
               return "";

           }break;
       default:
           liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Instruction inconnu";
           break;
       }

   }else
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Erreur d'identfication d'instruction";
    return "";
}

QString Compilateur::Compiler_Affectation(QDomElement instruction,Context_Memoire *context_memoire,int ligne)
{
    /// --------------- TRAITEMENT VARIABLE A AFFECTATION -----------------------
    QString variable = Pas_espace(instruction.attribute("var"));
    if(!variable.isEmpty())
    {

    }
     else
         liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Variable d'affectation indeffinit";

    /// ---------------- TRAITELENT EXRESSION D'AFFECTATION ---------------------
    QString expression = Pas_espace(instruction.attribute("exp"));
    if(!expression.isEmpty())
    {

    }else
        liste_erreur<<"Ligne : " + QString::number(ligne) + "-> expression d'affectation indeffinit";
    return "";
}

QString Compilateur::Compiler_Lecture(QDomElement instruction,Context_Memoire *context_memoire,int ligne)
{
    /// ---------------- TRAITEMENT VARIABLE A LECTURE ----------------------------
    QString variable = Pas_espace(instruction.attribute("var"));
    if(!variable.isEmpty())
    {

    }else
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> variable à lecture indeffinit";
    /// ---------------- TRAITEMENT MESSAGE DE LECTURE ----------------------------
    QString message_lec = Pas_espace(instruction.attribute("msg"));
    if(!message_lec.isEmpty())
    {

    }
    return "";
}

QString Compilateur::Compiler_Ecriture(QDomElement instruction, Compilateur::Context_Memoire *context_memoire, int ligne)
{
    /// ---------------- TRAITEMENT MESSAGE D'ECRITURE ----------------------------
    QString message = Pas_espace(instruction.attribute("msg"));
    if(!message.isEmpty())
    {

    }
    else
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> Message indeffinit";
    return "";
}

QString Compilateur::Compiler_Pour_Faire(QDomElement instruction, Compilateur::Context_Memoire *contextMemoire, int ligne)
{
    /// ----------------------- TRAITEMENT COMPTEUR -----------------------------------
    QString compteur = Pas_espace(instruction.attribute("cmp"));
    if(!compteur.isEmpty())
    {

    }else
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> compteur indeffinit";
    /// ----------------------- TRAITEMENT VALEUR INITIALE ----------------------------
    QString val_init = Pas_espace(instruction.attribute("vi"));

    if(!val_init.isEmpty())
    {

    }else
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> valeur initiale indeffinit";
    /// ---------------------- TRAITEMENT VALEUR FINALE -------------------------------
    QString val_fin = Pas_espace(instruction.attribute("vf"));

    if(!val_fin.isEmpty())
    {

    }else
        liste_erreur<<"Ligne : " + QString::number(ligne) + " -> valeur finale indeffinit";
    /// -------------------- TRAITEMENT PAS D ' INCRIMENTATION -------------------------
        QString pas_inc = Pas_espace(instruction.attribute("pas"));
        if(!pas_inc.isEmpty())
        {
            bool ok;
            int pas = pas_inc.toInt(&ok);
            if(ok)
            {
                if(!pas)
                    liste_erreur<<"Ligne : " + QString::number(ligne) + " -> pas d'incrimentation doit avoir un valeur different de 0 ";
            }else
                liste_erreur<<"Ligne : " + QString::number(ligne) + " -> pas d'incrimentation ne correspand pas à un nombre entier ";

        }else
            liste_erreur<<"Ligne : " + QString::number(ligne) + " -> pas d'incrimentation indeffinit";
    /// ------------------- CONVERTION TOUT OUTPROGRAMME ---------------------------------
        return "";
}

QString Compilateur::Compiler_Appelle_Procedure(QDomElement instruction, Compilateur::Context_Memoire *contextMemoire, int ligne)
{
   return "";
}


QString Compilateur::Controle_NomType(QString nomType)
{
    nomType = Pas_espace(nomType);
    if(nomType.isEmpty())
        return "Nom de type est indeffint";
    if(!nomType.at(0).isLetter())
        return "Nom de type doit commencé par une lettre";
    for(int i = 0; i < nomType.size();i++)
    {
        if(nomType.at(i).isSpace())
            return "Nom de type contient un espace ";
        if(!nomType.at(i).isLetterOrNumber() && nomType.at(i) != '_')
            return QString("Nom de type contient un symbole '").append(nomType.at(i)) + "'";
    }
    if(!nomType.isEmpty())
    {
        if(liste_motsJS.contains(nomType))
            return "Nom de type interdit";
        if(liste_Constantes.contains(nomType))
            return "Nom de type est déja declare comme un constante";
        if(liste_types.contains(nomType))
            return "Nom de type est déja declare";
    }
    return "";
}

QString Compilateur::typeRetournExression(QString expression, Context_Memoire *context)
{
    // a = a + b - (a + 5) * 2;
    // b = a = 2 ET a < 2 OU( a == 3 ET 4 <= 3)
}

Compilateur::Context_Memoire::Context_Memoire(Compilateur *Compilateur)
{
    listeSimleTypes<<"entier"<<"reel"<<"chaine"<<"caractere"<<"booleen";
    listeSimleTypes_Pointeurs<<"@entier"<<"@reel"<<"@chaine"<<"@caractere"<<"@booleen";
    THIS = Compilateur;
    RacineContext = documentContext.createElement("context");
    listeOperateursEntieres<<"+"<<"-"<<"*"<<"/"<<" MOD "<<" DIV ";
    listeOperateursBooleens<<"=" << "<" << "<=" << ">" << ">=" << " NON " << " OU " << " ET ";
}

void Compilateur::Context_Memoire::AjouterVariable(QString nom, QString type)
{
    QDomElement var = documentContext.createElement("var");
    var.setAttribute("nom",nom);
    var.setAttribute("type",type);
    RacineContext.appendChild(var);
    listeNomVariables<<nom;
   / *QDomElement variable_memoire = documentContext.createElement("var");
   nom = THIS->Pas_espace(nom);
   type = THIS->Pas_espace(type);
   if(!type.isEmpty() && !type.isEmpty())
   {
       EclaterVariable(nom,type,&variable_memoire);
       RacineContext.appendChild(variable_memoire);

   }
   documentContext.appendChild(RacineContext);
   * /
}

QString Compilateur::Context_Memoire::typeVariable(QString variable)
{
    while (variable.contains(' ')) { variable = variable.remove(' ');}if(variable.isEmpty())return "";

    QString base_nom = "";
    int i = 0;
    QChar T;
    while (i < variable.size()) {
        T = variable.at(i);
        if(!T.isLetterOrNumber() && T != '_')
        {
            if(T == '[' || T == '.' || T == '@')
            {
               break;
            }
             else
            {
              qDebug()<<"type var Erreur de syntaxe "<<variable;
            }

        }else {
            base_nom.append(variable.at(i));
            i++;
        }
    }

    QString divition = "";

    while (i < variable.size()) {
        divition.append(variable.at(i));
    }

    return "";
}

void Compilateur::Context_Memoire::EclaterVariable(QString nom, QString type,QDomElement * elm_SVar)
{
    if(listeSimleTypes.contains(type))
    {
        elm_SVar->setAttribute("nom",nom);
        elm_SVar->setAttribute("type",type);
    }else
        if(listeSimleTypes_Pointeurs.contains(type))
        {
            elm_SVar->setAttribute("nom",nom + "@");
            elm_SVar->setAttribute("type",type);
        }
        else
        {
            elm_SVar->setAttribute("nom",nom);
            elm_SVar->setAttribute("type",type);

            QString genreType = "";
            if(!type.isEmpty())
                if(type.at(0) == '@')
                {
                    nom = nom + "@";
                    type.remove(0,1);
                    return;
                }

            ///------------------- ID TYPE
            QDomElement elmType;

            QDomNodeList Liste_TypesC = THIS->documentAlgorithme.firstChildElement().firstChildElement("types").childNodes();
            for(int i = 0; i < Liste_TypesC.size();i++)
            {
                if(THIS->Pas_espace(Liste_TypesC.at(i).toElement().attribute("name")) == THIS->Pas_espace(type))
                {
                    elmType = Liste_TypesC.at(i).toElement();
                    if(!elmType.tagName().isEmpty())
                        genreType = elmType.tagName();
                }
            }
            if(elmType.isNull())
            {
                qDebug()<<"elmtype null";
                return;
            }
            /// --------------------------
            QString Nnom = "",Ntype = "";

            if(genreType == "enreg")
            {
                QDomNodeList listeChamps = elmType.elementsByTagName("champ");
                for(int i = 0; i < listeChamps.size();i++)
                {
                    Nnom = THIS->Pas_espace(listeChamps.at(i).toElement().attribute("name"));
                    Ntype = THIS->Pas_espace(listeChamps.at(i).toElement().attribute("type"));
                    QDomElement elm_NSSVar = documentContext.createElement("var");
                    if(!Nnom.isEmpty() && !Ntype.isEmpty())
                    {
                        EclaterVariable(nom + "." + Nnom,Ntype,&elm_NSSVar);
                        elm_SVar->appendChild(elm_NSSVar);
                    }
                }
            }else
                if(genreType == "tab")
                {
                    bool ok;
                    QString nbrlignes = THIS->Pas_espace(elmType.attribute("taille"));

                    int taille = nbrlignes.toInt(&ok);
                    if(ok)
                    {
                        for(int i = 1; i <= taille;i++)
                        {
                            Nnom = nom + "[" + QString::number(i) + "]";
                            Ntype = THIS->Pas_espace(elmType.attribute("contenu"));
                            if(!Ntype.isEmpty())
                            {
                                QDomElement elm_NSSVar = documentContext.createElement("var");
                                EclaterVariable(Nnom,Ntype,&elm_NSSVar);
                                elm_SVar->appendChild(elm_NSSVar);
                            }
                        }
                    }
                }else
                    if(genreType == "mat")
                    {
                        bool ok;
                        QString nbrligne = THIS->Pas_espace(elmType.attribute("ligne")),nbrcolonne = THIS->Pas_espace(elmType.attribute("colonne"));
                        int NL = nbrligne.toInt(&ok);
                        int NC;
                        if(ok)
                            NC = nbrcolonne.toInt(&ok);
                        if(ok)
                        {
                            for(int l = 1; l < NL;l++)
                            {

                                for(int c = 1; c < NC;c++)
                                {
                                    Nnom = nom + "[" + QString::number(l) + "][" + QString::number(c) + "]";
                                    Ntype = THIS->Pas_espace(elmType.attribute("contenu"));
                                    if(!Ntype.isEmpty())
                                    {
                                        QDomElement elm_NSSVar = documentContext.createElement("var");;
                                        EclaterVariable(Nnom,Ntype,&elm_NSSVar);
                                        elm_SVar->appendChild(elm_NSSVar);
                                    }
                                }
                            }
                        }
                    }else
                        if(genreType == "fich")
                        {

                        }else
                        {
                            qDebug()<<"eclat Erreur";
                        }

           // elm_SVar->appendChild(elm_NSVar);
        }

}
*/
