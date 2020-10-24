#include <iostream>
#include <compilateur.h>
#include<lexicalanalyser.h>

using namespace std;

LexicalAnalyser a ;
SyntaxicAnalyser s;

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

int main(int argc , char ** argv[])
{

    try
    {
        QString expression;
        /*if(argc > 1)
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
        */
        //expression = "12 * 3 ) + 3";
         a.setStream(expression);

         // + - ANALYSE LEXICALE
             //LexicalAnalyse();
         // - - ANALYSE LEXICALE

         // + ANALYSE SYNATXIC
             //SyntaxicAnalyse();
         // - ANALYSE SYNTAXIC


         // + ANALYSE EXPRESSIONS
         try{
             expression = "NON(4 + (4 * 6)) <= 5 ET NON (FN test(2,) = (12 >= 3))";
             a.setStream(expression);
             NodeExpression * exp = s.AnalyseExpression(&a,false);
             cout << "****************************************"<<endl<<"*           ANALYSE EXPRESSION          *"<<endl<< "****************************************" << endl;
             //cout << DebugAnalyseExpression(exp)<<endl;//2 ** 3 - 3 / ()
             cout << " Expression string  : "<< expression.toStdString() <<endl<<exp->toString()<<endl;
             qDebug()<<s.endToken->toString();
         }
         catch(SyntaxicError error)
         {
             //system("cls");
             cout << "****************************************"<<endl<<"*          ANALYSE SYNTAXIC           *"<<endl<< "****************************************" << endl;
             cout << "__________________________________________________________________________"<<endl<<endl;
             cout << error.toString().toStdString() << endl;

             cout << endl<< " " << expression.toStdString()<<endl;
             int i ;
             for( i = 0; i < error.getcolumnLigne();i++)
                 cout<< "_";
             cout << "^" <<endl;
         }
         catch(LexicalError error)
         {
             system("cls");
             cout << "****************************************"<<endl<<"*           ANALYSE LEXICALE           *"<<endl<< "****************************************" << endl;
             cout << "__________________________________________________________________________"<<endl<<endl;
             cout << error.toString().toStdString() << endl;

             cout << endl<< " " << expression.toStdString()<<endl;
             int i;
             for( i = 0; i < error.getcolumnLigne();i++)
                 cout<< "_";
             cout << "^" <<endl;

         }


         // - ANALYSE EXPRESSIONS
    }catch(std::string error)
    {
        cout << "Program logic error : " + error << endl;
    }
    catch(QString error)
    {
        cout << "Program logic error : " + error.toStdString() << endl;
    }

    cout <<endl;
    return 0;
}

/*
 * std::string DebugAnalyseExpression(NodeExpression * expression)
{
    std::string str = "";

    try
    {
        while(expression)
        {
            qDebug()<<"DEBUG"<<expression->hasExpressionOperator();
            if(dynamic_cast<Reference*>(expression))
            {
                str += dynamic_cast<Reference*>(expression)->toString();
                if(expression->hasExpressionOperator())
                    expression = dynamic_cast<Reference*>(expression)->getExpressionOperator()->SecondOperand;
                else
                    expression = NULL;
            }
            else
            if(dynamic_cast<ConstValue*>(expression))
            {
               str  += dynamic_cast<ConstValue*>(expression)->toString();
               if(expression->hasExpressionOperator())
                   expression = dynamic_cast<ConstValue*>(expression)->getExpressionOperator()->SecondOperand;
               else
                   expression = NULL;
            }
            else
            if(dynamic_cast<FctCall*>(expression))
            {
                str += dynamic_cast<FctCall*>(expression)->toString();
                if(expression->hasExpressionOperator())
                    expression = dynamic_cast<FctCall*>(expression)->getExpressionOperator()->SecondOperand;
                else
                    expression = NULL;
            }
            else
            if(dynamic_cast<Expression*>(expression))
            {
                str += "( " + DebugAnalyseExpression(dynamic_cast<Expression*>(expression)->GetNode()) + ")";
                if(expression->hasExpressionOperator())
                {
                    str += " " + expression->getExpressionOperator()->value->Value() + " ";
                    expression = dynamic_cast<Expression*>(expression)->getExpressionOperator()->SecondOperand;
                }
                else
                    expression = NULL ;
            }
            else
            if(dynamic_cast<ExpressionWithSignelOperator*>(expression))
            {
                str += dynamic_cast<ExpressionWithSignelOperator*>(expression)->getOperator()->Value() + " ";
                str += DebugAnalyseExpression(dynamic_cast<ExpressionWithSignelOperator*>(expression)->GetNode());
                if(expression->hasExpressionOperator())
                {
                    str += " " + expression->getExpressionOperator()->value->Value() + " ";
                    expression = dynamic_cast<ExpressionWithSignelOperator*>(expression)->getExpressionOperator()->SecondOperand;
                }
                else
                    expression = NULL;
            }
            else
            {
                qDebug()<<"No casting expression";
            }

        }
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
    return str;
}
*/
