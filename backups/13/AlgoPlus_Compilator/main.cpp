#include <iostream>
#include <compilateur.h>
#include<lexicalanalyser.h>

using namespace std;

LexicalAnalyser lexicalAnalyser ;
SyntaxicAnalyser syntaxicAnalyser;

string spacerSpacers15(string pattern){
    pattern = "'" + pattern + "'";
    if(pattern.size() >= 15)return pattern;
    string result = "";
    for(int i = pattern.size(); i < 15;i++)result += " ";
    return pattern + result;
}

std::string ReadStream(std::string file_name){

    QString expression = "";
    cout<<"Reading file stream" << file_name <<endl<< " ..."<<endl;
    QFile file(QString::fromStdString(file_name));
    if(QFileInfo(file).suffix() != "alg")
    {
        perror("File stream '" + QString::fromStdString(file_name).toLocal8Bit() + "' is not a algorithm program source!");
        exit(1);
    }
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString expression = "";
        QTextStream in(&file);
        expression = in.readAll();

        if(expression.isEmpty())
        {
            system("cls");
            system("color c");
            perror("cannot compile : '" +   QString::fromStdString(file_name).toLocal8Bit() + "' file is empty ");
            exit(1);
        }
        else
        {
            lexicalAnalyser.setStream(expression);
            //char response;
            //cout<<endl<<expression.toStdString()<<endl<<"do u wante to continue .(N/*) : ";
            //cin>>response;
            //if(response == 'n' || response == 'N')
            //    exit(0);
        }

    }else
    {
        system("cls");
        system("color c");
        perror("cannot open file with name : " + QString::fromStdString(file_name).toLocal8Bit());
        exit(1);
    }

    return expression.toStdString();
}

void LexicalAnalyse(){
    cout << "****************************************"<<endl<<"*           ANALYSE LEXICALE           *"<<endl<< "****************************************" << endl;
    Token * token;
    QString shit = "";
        try{
        token = lexicalAnalyser.NextToken();
        while (token != NULL ){
            //cout << endl<<"(" << token->getLineNumber() << ":" << token->getColumnNumber() << ")\t Token  : " + spacerSpacers15(token->Value()) + "\t ,Nature :  " <<  token->stringNature() << endl;
            //if(lexicalAnalyser.lastToken)cout<<lexicalAnalyser.lastToken->toString().toStdString()<<endl;

            token = lexicalAnalyser.NextToken();
        }
        lexicalAnalyser.SeekToken(lexicalAnalyser.lastToken);
        while(token = lexicalAnalyser.BackToken())cout<<token->toString().toStdString()<<endl;

        //QFile * f = new QFile("C://Users//Med_Mahdi_Maarouf//logAlgo.txt");
        //f->open(QIODevice::WriteOnly | QIODevice::Text);
        //QTextStream *s = new QTextStream(f);
        //*s<<shit;
        //f->close();
    }catch(LexicalError error)
    {
        system("cls");
        cout << "****************************************"<<endl<<"*           ANALYSE LEXICALE           *"<<endl<< "****************************************" << endl;
        cout << "__________________________________________________________________________"<<endl<<endl;
        cout << error.toString().toStdString() << endl;
    }

    cout<<endl;
}

void SyntaxicAnalyse(){
    // -- ANALYSE SYNTAXIC
    cout << "******************************************"<<endl<<"*           ANALYSE SYNTAXIC           *"<<endl<< "******************************************" << endl;
    try{
        syntaxicAnalyser.AnalyseMainScope(&lexicalAnalyser);
        std::cout<<Compilateur::ParseTree->toString();
       // qDebug()<<Compilateur::ParseTree->getDebutStatment()->hasChildStatments();
    }catch(SyntaxicError error)
    {
        //system("cls");
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

void AnalyseExpression(std::string exp_str){
    try{
        lexicalAnalyser.setStream(QString::fromStdString(exp_str));
        NodeExpression * exp = syntaxicAnalyser.AnalyseExpression(&lexicalAnalyser);
        if(exp == NULL) throw string("NO EXPRESSION FOUND");
        cout << "****************************************"<<endl<<"*           ANALYSE EXPRESSION          *"<<endl<< "****************************************" << endl;
        cout << " Pattern expression  : "<< exp_str <<endl<<"\n Analysed expression -> "<< exp->toString()<<endl<<" Current Token : " << lexicalAnalyser.currentToken->Value();

    }
    catch(SyntaxicError error)
    {
        //system("cls");
        cout << "****************************************"<<endl<<"*          ANALYSE SYNTAXIC           *"<<endl<< "****************************************" << endl;
        cout << "__________________________________________________________________________"<<endl<<endl;
        cout << error.toString().toStdString() << endl;

        cout << endl<< " " << exp_str <<endl;
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

        cout << endl<< " " << exp_str <<endl;
        int i;
        for( i = 0; i < error.getcolumnLigne();i++)
            cout<< "_";
        cout << "^" <<endl;

    }
    catch(string err){
        //system("cls");
        cout << "****************************************"<<endl<<"*          ANALYSE EXPRESSION           *"<<endl<< "****************************************" << endl;
        cout << "__________________________________________________________________________"<<endl<<endl;
        cout << err<< endl;

    }
}

void autoExpressionTest(){
    string pattern = "";
    char c = 'o';

    while(c == 'o' || c == 'O'){
        cout<<"Ecrire l'expression souhaité : ";
        cin>> pattern;
        try{
            AnalyseExpression(pattern);
        }catch(std::string error){
            cout << "Program logic error : " + error << endl;
        }
        catch(QString error){
            cout << "Program logic error : " + error.toStdString() << endl;
        }
        do{
            cout<<"Voulez vous continuer O(Oui)/N(Non) : ";
            cin>>c;
        }while (c != 'N' && c != 'n' && c != 'o' && c != 'O' );
    }
}

int main(int argc , char ** argv[]){

    try
    {
         // + - ANALYSE LEXICALE
             //ReadStream("Algorithme5.alg");
             //LexicalAnalyse();
         // - - ANALYSE LEXICALE

         // + ANALYSE SYNATXIC
             ReadStream("Algorithme1.alg");
             SyntaxicAnalyse();
         // - ANALYSE SYNTAXIC

         // + ANALYSE EXPRESSIONS
            /**
             *FN test()@
             *FN test()@.value
             *(FN test()@).value
             **/


            //autoExpressionTest();
            //AnalyseExpression("(FN test()@).value");
            //lexicalAnalyser.setStream("(2 * X + 3 * Y + 5 = 0 ET 5 <> V OU BOOL) * 3");
            //LexicalAnalyse();
        // - ANALYSE EXPRESSIONS

    }catch(std::string error)
    {
        cout << "Program logic error : " + error << endl;
    }
    catch(QString error)
    {
        cout << "Program logic error : " + error.toStdString() << endl;
    }

    endMain:{
        cout <<endl;
        return 0;
    }
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

