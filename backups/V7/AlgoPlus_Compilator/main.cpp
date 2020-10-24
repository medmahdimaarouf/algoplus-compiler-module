#include <iostream>
#include <compilateur.h>
#include<lexicalanalyser.h>

using namespace std;

LexicalAnalyser a ;
SyntaxicAnalyser s;

std::string ReadFileStream(std::string arg)
{

}

void LexicalAnalyse()
{
    cout << "****************************************"<<endl<<"*           ANALYSE LEXICALE           *"<<endl<< "****************************************" << endl;
    Token *t;
        try{
        t = a.NextToken();
        string nat = "No nature detected";
        while (t != NULL ){
            switch (t->Nature()) {
            case Punctuation:nat =  "Punctuation";break;
            case LogicOperator:nat = "LogicOperator";break;
            case LI:nat = "LI";break;
            case RI:nat = "RI";break;
            case Lp:nat = "Lp";break;
            case Rp:nat = "Rp";break;
            case ArithmeticOperator:nat = "ArithmeticOperator";break;
            case NUMBER:nat = "NUMBER";break;
            case Reel:nat = "Reel";break;
            case ID:nat = "ID";break;
            case STR:nat = "STR";break;
            case CHAR:nat = "CHAR";break;
            case AssignValue:nat = "AssignValue";break;
            case AssignType:nat = "AssignType";break;
            case LocationSpecifier:nat = "LocationSpecifier";break;
            case KeyWord: nat  = "KeyWord";break;
            }

            cout << "(" << t->getLineNumber() << ":" << t->getColumnNumber() << ")\t Token  : " + t->Value() + " \t \t \t \t ,Nature :  " <<  nat << endl;
            t = a.NextToken();
        }
    }catch(LexicalError error)
    {
        system("cls");
        cout << "****************************************"<<endl<<"*           ANALYSE LEXICALE           *"<<endl<< "****************************************" << endl;
        cout << "__________________________________________________________________________"<<endl<<endl;
        cout << error.toString().toStdString() << endl;
    }

    cout<<endl;
}

void SyntaxicAnalyse()
{
    // -- ANALYSE SYNTAXIC
    cout << "******************************************"<<endl<<"*           ANALYSE SYNTAXIC           *"<<endl<< "******************************************" << endl;
    try{
        s.AnalyseMainScope(&a);
        std::cout<<Compilateur::ParseTree->toString();
    }catch(SyntaxicError error)
    {
        system("cls");
        cout << "****************************************"<<endl<<"*          ANALYSE SYNTAXIC           *"<<endl<< "****************************************" << endl;
        cout << "__________________________________________________________________________"<<endl<<endl;
        cout << error.toString().toStdString() << endl;
    }
    catch(LexicalError error)
    {
        system("cls");
        cout << "****************************************"<<endl<<"*           ANALYSE LEXICALE           *"<<endl<< "****************************************" << endl;
        cout << "__________________________________________________________________________"<<endl<<endl;
        cout << error.toString().toStdString() << endl;
    }

}

void DebugAnalyseExpression(std::string expression)
{
    try
    {
        LexicalAnalyser lex;
        SyntaxicAnalyser s2;
        lex.setStream(QString::fromStdString(expression));
        Expression * expr = s2.AnalyseExpression(&lex);
        cout << "****************************************"<<endl<<"*           ANALYSE EXPRESSION          *"<<endl<< "****************************************" << endl;
        std::string str = "";

        while(expr)
        {
            qDebug()<<"DEBUG"<<expr->hasExpressionOperator();
            if(dynamic_cast<Reference*>(expr))
            {
                str += dynamic_cast<Reference*>(expr)->toString();
                if(expr->hasExpressionOperator())
                    expr = dynamic_cast<Reference*>(expr)->getExpressionOperator()->SecondOperand;
                else
                    expr = NULL;
            }
            else
            if(dynamic_cast<ConstValue*>(expr))
            {
               str  += dynamic_cast<ConstValue*>(expr)->toString();
               if(expr->hasExpressionOperator())
                   expr = dynamic_cast<ConstValue*>(expr)->getExpressionOperator()->SecondOperand;
               else
                   expr = NULL;
            }
            else
            if(dynamic_cast<FctCall*>(expr))
            {
                str += dynamic_cast<FctCall*>(expr)->toString();
                if(expr->hasExpressionOperator())
                    expr = dynamic_cast<FctCall*>(expr)->getExpressionOperator()->SecondOperand;
                else
                    expr = NULL;
            }
            else
            {
                str += "no casting expression";
                expr = NULL;
            }

        }
        cout <<str<< endl;

    }
    catch(SyntaxicError error)
    {
        system("cls");
        cout << "****************************************"<<endl<<"*          ANALYSE SYNTAXIC           *"<<endl<< "****************************************" << endl;
        cout << "__________________________________________________________________________"<<endl<<endl;
        cout << error.toString().toStdString() << endl;
    }
    catch(LexicalError error)
    {
        system("cls");
        cout << "****************************************"<<endl<<"*           ANALYSE LEXICALE           *"<<endl<< "****************************************" << endl;
        cout << "__________________________________________________________________________"<<endl<<endl;
        cout << error.toString().toStdString() << endl;
    }
}

int main(int argc , char ** argv[])
{
    try
    {
        //cout << "argc : " << argc << "argv : " << *argv[0]<<endl;
        QString expression;
        if(argc > 1)
        {
            QString file_name = "./algorithme4.alg";
            qDebug()<<"File Algo : " + file_name;
            QFile file(file_name);
            if(file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&file);
                expression = in.readAll();

            }else
            {
                system("cls");
                system("color c");
                perror("cannot open file with name : " + file_name.toLocal8Bit());
                exit(1);
            }
        }
        // -- ANALYSE LEXICALE
         a.setStream(expression);
         //LexicalAnalyse();
         //SyntaxicAnalyse();
         DebugAnalyseExpression("4 + * 4 * ");//2 ** 3 - 3
    }catch(std::string error)
    {
        cout << "Program logic error : " + error << endl;
    }
    catch(QString error)
    {
        cout << "Program logic error : " + error.toStdString() << endl;
    }

    return 0;
}

