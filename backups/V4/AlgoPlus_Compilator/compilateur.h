#ifndef COMPILATEUR_H
#define COMPILATEUR_H

#include <QObject>
#include<QtXml>
#include<QMap>
#include "syntaxicanalyser.h"
#include "mainscope.h"
#include "warning.h"
class Compilateur : public QObject
{
    Q_OBJECT
public:
    explicit Compilateur(QObject *parent);
    static MainScope * ParseTree;
    void Compiler(const QDomDocument documentAlgorithme);
    void Compiler();
    void Clear();
private slots:
    void emitError(const CompilationError error);
    void emitWarning(const Warning warning);
signals:
    void hasError(const CompilationError error);
    void hasWarning(const Warning warning);
    void CompilationFinished();
    void CompilationStarted();
    void CompilationInterrepted();
private:
    QDomDocument documentAlgorithme;
    //SyntaxicAnalyser * syntaxicAnalyser;
    QList<CompilationError> listErrors;
    QList<Warning> listWarning;
};

/*
private:
    class Context_Memoire
    {

    public:
        Context_Memoire(Compilateur *Compilateur);

        void AjouterVariable(QString nom,QString type);
        QString typeVariable(QString variable);

        / *void AjouterFonction();
        void Ajouter_procedure();* /

    private:
        QStringList listeOperateursEntieres;
        QStringList listeOperateursBooleens;
        QStringList listeSimleTypes;
        QStringList listeSimleTypes_Pointeurs;
        QStringList listeNomVariables;
        QDomElement RacineContext;
        void EclaterVariable(QString nom, QString type, QDomElement *elm_SVar);
        Compilateur * THIS;
        QDomDocument documentContext;
    };

    QString Pas_espace(QString chaine);
    QString Compiler_constante(QDomElement elm_constante, int ligne);
    QString Compiler_Tableau(QDomElement elmTab,int ligne);
    QString Compiler_Matrice(QDomElement elmMat,int ligne);
    QString Compiler_Enregistrement(QDomElement elmEnreg, int *ligne);
    QString Compiler_Fichier(QDomElement elmFich,int ligne);
    QString Compiler_Champ(QDomElement champ, int ligne, QStringList *listeChamps, QString nomEnreg);
    QString Compiler_Variable(QDomElement elmvar, int ligne, QStringList *listeVars, Context_Memoire *contextMemoire);
    QString Compiler_Fonction(QDomElement fonction,int *ligne);
    QString Compiler_Procedure(QDomElement procedure, int *ligne);
    QString Compiler_Parametre(bool fonction, QDomElement parametre, int ligne, QStringList *listeParametre);
    QString Compiler_DebutProgramme(QDomNodeList Instructions, Context_Memoire *ContextMemoireProgramme, int * ligne);
    QString Compiler_Instruction(QDomElement instruction, Context_Memoire *contextMemoire, int ligne);

    QString Compiler_Affectation(QDomElement instruction, Context_Memoire * context_memoire, int ligne);
    QString Compiler_Lecture(QDomElement instruction, Context_Memoire * context_memoire, int ligne);
    QString Compiler_Ecriture(QDomElement instruction, Context_Memoire * context_memoire, int ligne);
    QString Compiler_Pour_Faire(QDomElement instruction, Context_Memoire *contextMemoire, int ligne);
    QString Compiler_Appelle_Procedure(QDomElement instruction, Context_Memoire *contextMemoire, int ligne);

    QString Controle_NomType(QString nomType);

    QString outPutProgram;
    bool A_constantes,A_types,A_variables;

    Context_Memoire * contextProgramme_Principale;

    // nouveaux
    QString typeRetournExression(QString expression,Context_Memoire * context);

};
*/
#endif // COMPILATEUR_H
