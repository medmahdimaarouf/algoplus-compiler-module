#include<debuger.h>
char Debuger::endl = '\n';
#include <iostream>
#include <compilateur.h>
#include<QFile>
#include<QFileInfo>
#include<QTextStream>
using namespace std;

StdString spacerSpacers15(StdString pattern){

    pattern = "'" + pattern + "'";
    if(pattern.size() >= 15)return pattern;
    StdString result = StdString("");
    for(int i = pattern.size(); i < 15;i++)result += " ";
    return pattern + result;
}

StdString ReadStream(StdString file_name){
/*
    if(file_name.isEmpty())throw 0;

    QTextStream * textStream;
    QFile file(file_name);
    StdString fileContent = StdString("");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))throw 1;
    if(!file.isReadable())throw 2;
    if(QFileInfo(file).suffix() != "alg")throw 3;
    textStream =  new QTextStream(&file);
    if((fileContent = textStream->readAll().toStdString()).isEmpty())throw 4;

    return fileContent;
*/
}


void LexicalAnalyse(LexicalAnalyser lexicalAnalyser){
    std::cout << "****************************************"<<endl<<"*           ANALYSE LEXICALE           *"<<endl<< "****************************************" << endl;
    Token * token;

   try{
        while((token = lexicalAnalyser.NextToken()) != NULL){
            std::cout << endl<<"(" << token->getLineNumber() << ":" << token->getColumnNumber() << ")\t Token  : " + spacerSpacers15(token->Value()).toStdString() + "\t ,Nature :  " <<  token->stringNature().toStdString() << endl;
        }

    }catch(LexicalError error)
    {
        system("cls");
        std::cout << "****************************************"<<endl<<"*           ANALYSE LEXICALE           *"<<endl<< "****************************************" << endl;
        std::cout << "__________________________________________________________________________"<<endl<<endl;
        std::cout << error.toString().toStdString() << endl;
    }

    std::cout<<endl;
}


void SyntaxicAnalyse(LexicalAnalyser lexicalAnalyser,SyntaxicAnalyser syntaxicAnalyser){
    // -- ANALYSE SYNTAXIC
    std::cout << "******************************************"<<std::endl<<"*           ANALYSE SYNTAXIC           *"<<endl<< "******************************************" << endl;
    try{
        syntaxicAnalyser.AnalyseMainScope(&lexicalAnalyser);
        std::cout<<Compilateur::ParseTree->toString().toStdString();
    }catch(SyntaxicError error)
    {
        //system("cls");
        std::cout << "****************************************"<<endl<<"*          ANALYSE SYNTAXIC           *"<<endl<< "****************************************" << endl;
        std::cout << "__________________________________________________________________________"<<endl<<endl;
        std::cout << error.toString().toStdString() << endl;
    }
    catch(LexicalError error)
    {
        system("cls");
        std::cout << "****************************************"<<endl<<"*           ANALYSE LEXICALE           *"<<endl<< "****************************************" << endl;
        std::cout << "__________________________________________________________________________"<<endl<<endl;
        std::cout << error.toString().toStdString() << endl;
    }

}


void AnalyseExpression(StdString exp_str){
    LexicalAnalyser lexicalAnalyser;
    SyntaxicAnalyser syntaxicAnalyser;
    try{
        lexicalAnalyser.setStream(exp_str);
        NodeExpression * exp = syntaxicAnalyser.AnalyseExpression(&lexicalAnalyser);
        if(exp == NULL) throw StdString("NO EXPRESSION FOUND");
        std::cout << "****************************************"<<endl<<"*           ANALYSE EXPRESSION          *"<<endl<< "****************************************" << endl;
        std::cout << " Pattern expression  : "<< exp_str.toStdString() <<endl<<"\n Analysed expression -> "<< exp->toString().toStdString()<<endl<<" Current Token : " << lexicalAnalyser.getCurrentToken()->Value().toStdString();

    }
    catch(SyntaxicError error)
    {
        //system("cls");
        std::cout << "****************************************"<<endl<<"*          ANALYSE SYNTAXIC           *"<<endl<< "****************************************" << endl;
        std::cout << "__________________________________________________________________________"<<endl<<endl;
        std::cout << error.toString().toStdString() << endl;

        std::cout << endl<< " " << exp_str.toStdString() <<endl;
        int i ;
        for( i = 0; i < error.getcolumnLigne();i++)
            std::cout<< "_";
        std::cout << "^" <<endl;
    }
    catch(LexicalError error)
    {
        system("cls");
        std::cout << "****************************************"<<endl<<"*           ANALYSE LEXICALE           *"<<endl<< "****************************************" << endl;
        std::cout << "__________________________________________________________________________"<<endl<<endl;
        std::cout << error.toString().toStdString() << endl;

        std::cout << endl<< " " << exp_str.toStdString() <<endl;
        int i;
        for( i = 0; i < error.getcolumnLigne();i++)
            std::cout<< "_";
        std::cout << "^" <<endl;

    }
    catch(StdString err){
        //system("cls");
        std::cout << "****************************************"<<endl<<"*          ANALYSE EXPRESSION           *"<<endl<< "****************************************" << endl;
        std::cout << "__________________________________________________________________________"<<endl<<endl;
        std::cout << err.toStdString() << endl;

    }
}

void autoExpressionTest(){
    std::string pattern = "";
    char c = 'o';

    while(c == 'o' || c == 'O'){
        std::cout<<"Ecrire l'expression souhaité : ";
        std::cin>> pattern;
        try{
            AnalyseExpression(StdString::fromStdString(pattern));
        }catch(StdString error){
            std::cout << "Program logic error : " + error.toStdString() << endl;
        }
        catch(StdString error){
            std::cout << "Program logic error : " + error.toStdString() << endl;
        }
        do{
            std::cout<<"Voulez vous continuer O(Oui)/N(Non) : ";
            std::cin>>c;
        }while (c != 'N' && c != 'n' && c != 'o' && c != 'O' );
    }
}

int main(int argc , char ** argv[]){



    StdString string("");

    string  = "const char*1" + string + "const char*2";
    ObjectAlgo o;
    o.setName(StdString(""));
    o.setName(string);
    return 1;


    LexicalAnalyser lexicalAnalyser ;
    SyntaxicAnalyser syntaxicAnalyser;


    StdString filename = StdString("Algorithme5.alg");

    try{
        std::cout<<"Reading file stream" << filename.toStdString() <<std::endl<< " ..."<<endl;
        lexicalAnalyser.setStream(ReadStream(filename));

    }
    catch(int errorIndex){
        system("cls");
        system("color c");
        /*switch (errorIndex) {
            case 0:perror("cannot compile : '" +   filename.toLocal8Bit() + "' invalid name file '");break;
            case 1:perror("cannot compile : '" +   filename.toLocal8Bit() + "' can not open file '");break;
            case 2:perror("cannot compile : '" +   filename.toLocal8Bit() + "' can not read file '");break;
            case 3:perror("cannot compile : '" +   filename.toLocal8Bit() + "' can not support this type of file '");break;
            case 4:perror("cannot compile : '" +   filename.toLocal8Bit() + "'file is empty'");break;
            default:perror("cannot compile : '" +  filename.toLocal8Bit() + "' Unknown error '");break;
        }*/
        exit(1);
    }

    try
    {
         // + - ANALYSE LEXICALE
             //LexicalAnalyse(lexicalAnalyser);
         // - - ANALYSE LEXICALE

         // + ANALYSE SYNATXIC
             SyntaxicAnalyse(lexicalAnalyser,syntaxicAnalyser);
         // - ANALYSE SYNTAXIC

         // + ANALYSE EXPRESSIONS


            //autoExpressionTest();
            //AnalyseExpression("(FN test()@).value");
            //lexicalAnalyser.setStream("(2 * X + 3 * Y + 5 = 0 ET 5 <> V OU BOOL) * 3");
            //LexicalAnalyse();
        // - ANALYSE EXPRESSIONS

    }
    catch(StdString error){std::cout << "Program logic error : " + error.toStdString() << endl;}
    catch(StdString error){std::cout << "Program logic error : " + error.toStdString() << endl;}

    endMain:{std::cout <<endl;}

    return 0;
}
