#include "lexicalanalyser.h"
#include "XmlAlgConfig.inc"

int  LexicalAnalyser::Currentlignecode;
int  LexicalAnalyser::CurrentColumnlignecode;
char * LexicalAnalyser::keyWords[13] = {"POUR","SI","SELON","TANTEQUE","REPETER","JUSQU_A","FIN","NON","ET","OU","MOD","DIV","FN"};
QStringList listKeys;
LexicalAnalyser::LexicalAnalyser()
{
    currentIndex = 0;
    Currentlignecode = CurrentColumnlignecode = 1;
    // + ATTENTION ! : 'FIN' est un mot clé
    listKeys<<"ALGORITHME"<<"POUR"<<"SI"<<"SELON"<<"TANTEQUE"<<"REPETER"<<"JUSQU_A"<<"FN"<<"NON"<<"ET"<<"OU"<<"MOD"<<"DIV"<<"NIL"<<"NULLE"<<"FIN";
    // - ATTENTION !
}

Token * LexicalAnalyser::NextToken()
{

    //qDebug()<< "test : " << QString::fromStdString(lookAhead(3));
    if(currentIndex >= 0)
    {
        //qDebug()<<"tets : "<< Currentlignecode <<":"<< CurrentColumnlignecode;
        Token * t = new Token(Currentlignecode,CurrentColumnlignecode);
        switch (stream.toStdString()[currentIndex]) {
        case    '\"':{
            t->setNature(STR);
            t->setValue(str());
        }break;
        case    '\'':{
            t->setNature(CHAR);
            t->setValue(chr());
        }break;
 // --
        case    '<' :if( lookAhead(3) == "<--"){t->setNature(AssignValue);t->setValue(Advance(3));}
            break;
        case    '>' :if(lookAhead(2)[1] == '='){t->setNature(LogicOperator);t->setValue(Advance(2));}
            break;
        case    '=' :t->setNature(LogicOperator);
        case    '+' :
        case    '-' :

        case    '*' :
        case    '/' :{
            t->setValue(QString(stream[currentIndex]).toStdString());
            t->setNature(ArithmeticOperator);
            Advance();
        }break;

        case    '(' :t->setNature(Lp);
        case    ')' :t->setNature(Rp);
        case    '[' :t->setNature(LI);
        case    ']' :t->setNature(RI);
        case    ',' :t->setNature(Punctuation);
        case    '.' :if(lookAhead(2) == ".."){t->setNature(Punctuation);t->setValue(Advance(2));break;}
                     else t->setNature(Punctuation);
        case    '@' :t->setNature(LocationSpecifier);

        case    ':' :{
            t->setNature(AssignType);
            t->setValue(QString(stream[currentIndex]).toStdString());
            Advance();
        }break;
// --
        case    '\n':
        case    ' ' :
        case    '\r':
        case    '\t': {
                        delBlancs();
                        delete t;
                        t =  NextToken();
        } break;
        case    '{':{
            IngioreComment();
            delete t;
            t = NextToken();
        }break;
        default:
            if(stream[currentIndex].isDigit())
            {
                NumberT:
                    {
                        bool reel;
                        t->setValue(Number(&reel));
                        if(reel)
                            t->setNature(Reel);
                        else
                            t->setNature(NUMBER);
                    }
            }
            else
                if(stream[currentIndex].isLetter() || stream[currentIndex] == '_')
                {
                    t->setValue(Id());
                    if(!listKeys.contains(QString::fromStdString(t->Value()).toUpper()))
                        t->setNature(ID);
                    else
                        t->setNature(KeyWord);
                }
            else
                {
                    delete t;
                    throw LexicalError(Currentlignecode,CurrentColumnlignecode,QString(" Caractere illegal '" + QString(stream[currentIndex]) + "'").toStdString()) ;
                }

        }
        //if(t)qDebug()<< t->toString();
        return t;

    }else
        return NULL;
}

void LexicalAnalyser::Advance()
{
     if(currentIndex + 1 < this->stream.size())
     {
         currentIndex++;
         CurrentColumnlignecode++;
     }
     else
         currentIndex = -1;
}

void LexicalAnalyser::delBlancs()
{
    while (currentIndex && (stream[currentIndex] == '\t' || stream[currentIndex] == ' ' || stream[currentIndex] == '\n' || stream[currentIndex] == '\r' )) {
        if(stream[currentIndex] == '\n')
          {
            Currentlignecode++;
            CurrentColumnlignecode = 0;
           }
           Advance();
    }
}

void LexicalAnalyser::IngioreComment()
{
    Advance();
    while (currentIndex != -1 && stream[currentIndex] != '}') {
        if(stream[currentIndex] == '\n')
        {
            Currentlignecode++;
            CurrentColumnlignecode = 0;
        }
        else
        if(stream[currentIndex] == '{')
        {
            IngioreComment();
            if(currentIndex != -1)currentIndex--;
        }
        Advance();
    }
    if(currentIndex == -1)
        throw LexicalError(Currentlignecode,CurrentColumnlignecode,"Fin du commentaire '}' attendu");
    else
        Advance();

}

std::string LexicalAnalyser::Number(bool *reel)
{
    std::string number = "";
    *reel = false;
    while (currentIndex != -1 && this->stream[currentIndex].isNumber()) {
        number.append(QString(stream[currentIndex]).toStdString());
        Advance();
    }
    std::string look = lookAhead(2);
    if(look.size() == 2)
    {
        if(QChar(look[1]).isNumber() && look[0] == '.')
          {
            number.append(".");
            Advance();
            while (currentIndex != -1 && this->stream[currentIndex].isNumber()) {
                number.append(QString(stream[currentIndex]).toStdString());
                Advance();
            }
            *reel = true;
          }
    }
    return number;
}

std::string LexicalAnalyser::Id()
{
    std::string id = "";
    while (currentIndex != -1 && (this->stream[currentIndex].isLetterOrNumber() || this->stream[currentIndex] == '_')) {
        id.append(QString(stream[currentIndex]).toStdString());
        Advance();
    }

    return id;
}

std::string LexicalAnalyser::str()
{
    std::string str = "\"";
    Advance();
    while (currentIndex != -1 && stream.at(currentIndex) != '\"' && stream.at(currentIndex) != '\n') {
        str.append(QString(stream[currentIndex]).toStdString());
        Advance();
    }
    if(currentIndex != -1)
    {
       if(stream[currentIndex] == '\"')
       {
             str.append("\"");
             Advance();
             return str;
       }
    }
    throw LexicalError(Currentlignecode,CurrentColumnlignecode,"\" attendu ");
}

std::string LexicalAnalyser::chr()
{
    std::string chr = "\'";
    Advance();
    if(currentIndex != -1)
    {
        if(stream[currentIndex] == '\\')
        {
            qDebug()<< "i";
            chr.append("\\");
            Advance();
            switch (stream.toStdString()[currentIndex]) {
            case 'n' :
            case 'r' :
            case 't' :
            case '"' :
            case '\'':{
                chr.append(QString(stream[currentIndex]).toStdString());
                Advance();
                if(stream[currentIndex] == '\'')
                {
                    chr.append("'");
                    Advance();
                    return chr;
                }
            }
            default:
                throw LexicalError(Currentlignecode,CurrentColumnlignecode," Signfication erroné < " + QString(stream[currentIndex]).toStdString() + "\>");
            }
        }else
        {
            chr.append(QString(stream[currentIndex]).toStdString());
            Advance();
            if(currentIndex != -1)
            {
                if(stream[currentIndex] == '\'')
                {
                    chr.append("'");
                    Advance();
                    return chr;
                }
            }
        }

    }
    throw LexicalError(Currentlignecode,CurrentColumnlignecode," <'> attendu ");
}

std::string LexicalAnalyser::Advance(const int nbc)
{
    std::string str = lookAhead(nbc);
    for (int i = 0;currentIndex != -1 && i < nbc;i++){
        Advance();
    }
    return str;
}

std::string LexicalAnalyser::lookAhead(const int nbc)
{
    /*int i = 0;
    for(i = 1; i <= nbc && currentIndex + i < stream.size();i++);*/
    return stream.mid(currentIndex,nbc).toStdString();

}

TokenType LexicalAnalyser::NatureFromId(std::string id)
{
    /*if(this->listOperators.contains(QString(id).toUpper()))
    {
        if(QString(id).toUpper() == "DIV" || QString(id).toUpper() == "MOD")
            return ArithmeticOperator;
        else
            return LogicOperator;
    }else
        if(keysWord.contains(QString(id).toUpper()))
            return KeyWord;
        else
             return ID;
             */
}

bool LexicalAnalyser::isIdToken(QString token) {

    if(!token.at(0).isLetter() && token.at(token.size()-1) != '_' )
        return false;
    // MSG : Nom d'identificateur doit commencer par une lettrer ou '_'
    if(token.count(' ') != 0)
        return false;
    // MSG : Nom d'identificateur contient un espace
    foreach (QChar c, token) {
        if(c.isSymbol() && c != '_')
            return false;
    //MSG : Nom d'identificateur contient un symobole interdis < " + QString(c) + " >
    }
    return true;
}

QStringList LexicalAnalyser::toListTokens(QString expression){
        if(expression.isEmpty())
            return QStringList();
        QStringList listTokens;
        QString token;
        QChar c ;
        this->Currentlignecode = this->CurrentColumnlignecode = 1;

        for(int i = 0; i < expression.size();i++,this->CurrentColumnlignecode++)
        {
           c = expression.at(i);

           if(c == '"')  // CHECK IF IT IS A STRING
           {
               if(!token.isEmpty())
               {
                   listTokens << token ;
                   token.clear();
               }
               token.append(c);

               if(i+1 < expression.size())
               {
                    c = expression.at(++i);
                    for(; i < expression.size() && (c = expression.at(i)) != '"' && c != '\n';i++,CurrentColumnlignecode++)
                    {
                        token.append(c);
                    }
                    if(c == '"')
                    {
                        listTokens.append(token.append(c));
                        token.clear();
                        continue;
                    }

               }
               // HANDLE ERROR '"' NOT FOUNED !!
               qDebug() <<"(" << this->Currentlignecode << " : " << this->CurrentColumnlignecode - 1 << ")" <<  "Lexical Error -> '\"' not found " ;
               listTokens.clear();
               return listTokens;

           }
           else
               if(c == '\t'|| c == '\n' || c == ' ' || c == '(' || c == ')' || c == '[' || c == ']' || c == ',' || c == '.' || c == ':' ) // c == ';' //     SEPARTORS TOKENS
               {

                   if(!token.isEmpty())
                    {
                        listTokens.append(token);
                        token.clear();
                    }

                    if(c == '.' && expression.at(i + 1) == '.')
                     {
                          if(!token.isEmpty())
                          {
                           listTokens << token;
                           token.clear();
                          }
                          listTokens << "..";
                          i++;
                      }
                   else
                   if(c != ' ' && c != '\t' && c != '\n')
                       listTokens.append(QString(c));
                    else if(c == '\n')
                   {
                       this->Currentlignecode ++;
                       this->CurrentColumnlignecode = 0;
                   }

               }
           else
               if(c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>' )
               {
                    if(c == '<' || c == '>')
                      {
                         if(expression.at(i + 1) == '=')
                           {
                             if(!token.isEmpty())
                             {
                              listTokens << token;
                              token.clear();
                             }
                             listTokens<<QString(c).append('=');
                             i++;
                           }
                         else
                            if(c == '<' && expression.at(i+1) == '-' && expression.at(i + 2) == '-')
                            {
                                if(!token.isEmpty())
                                {
                                 listTokens << token;
                                 token.clear();
                                }

                                listTokens<< QString("<--");
                                i += 3;
                            }
                        else
                            {
                                if(!token.isEmpty())
                                {
                                    listTokens << token;
                                    token.clear();
                                }
                                listTokens << QString(c);
                            }
                     }
                     else
                     {
                        if(!token.isEmpty())
                        {
                            listTokens << token;
                            token.clear();
                        }
                        listTokens<< QString(c);
                     }
               }
           else
               if(c.isLetterOrNumber() || c == '_')
               {
                    token.append(c);
               }
           else
               {
                   //emit this->Handle_Error(LexicalError(this->Currentlignecode,this->CurrentColumnlignecode,QString("invalide token '" + QString(c) + "'")));
                   qDebug() <<"(" << this->Currentlignecode << " : " << this->CurrentColumnlignecode - 1 << ")" << "Lexical Error -> invalide token '" << c << "'" ;
                   listTokens.clear();
                   return listTokens;
               }
          // qDebug()<< "c : " << c << " i : " << i;
       }
        if(!listTokens.isEmpty())
        {
            listTokens << token;
            token.clear();
        }
        return listTokens;
}

void LexicalAnalyser::StartXMLAnalyse(QDomDocument xmlPattern){
    QDomElement root  = xmlPattern.documentElement();
    // ** CONSTS **
    QDomElement rootconsts = root.firstChildElement(XMLTAGNAME_ROOT_COSNTS);
    QDomNodeList listConsts_elements = rootconsts.elementsByTagName(XMLTAGNAME_CONST);
    for(int i = 0; i < listConsts_elements.size();i++)
    {
        QDomElement const_element = listConsts_elements.at(i).toElement();
        QString id_const = const_element.attribute(XMLATTRIBUTE_NAME_ITEM);
        QString value = const_element.attribute(XMLATTRIBUTE_CONST_VALUE);

        try{
            this->isIdToken(id_const);
        }catch(LexicalError error)
        {
            //emit this->Handle_Error(error);
        }
        try{
            //this->Check_ValueOFConst(value);
        }catch(LexicalError error)
        {
            //emit this->Handle_Error(error);
        }
    }
    // ** TYPES **

    QDomElement roottypes = root.firstChildElement(XMLTAGNAME_ROOT_TYPES);
    QDomNodeList listtypes_elements = roottypes.childNodes();
    for(int i = 0; i < listtypes_elements.size();i++)
    {
        QDomElement type_element = listtypes_elements.at(i).toElement();
        QString tagType = type_element.tagName();
        QString type_id = type_element.attribute(XMLATTRIBUTE_NAME_ITEM);
        try{
            this->isIdToken(type_id);
        }catch(LexicalError error)
        {
            //emit this->Handle_Error(error);
        }

        if(tagType == XMLTAGNAME_TYPE_RECORD)
        {
            QDomNodeList listFields = type_element.elementsByTagName(XMLTAGNAME_RECORD_FIELD);
            for(int j  = 0; j < listFields.size();i++)
            {
                QDomElement elmField = listFields.at(i).toElement();

                QString fieldName = elmField.attribute(XMLATTRIBUTE_NAME_ITEM);
                try{
                    this->isIdToken(fieldName);
                }catch(LexicalError error)
                {
                    //emit this->Handle_Error(error);
                }
                QString fieldType = elmField.attribute(XMLATTRIBUTE_FIELD_RCD_TYPE);
                try{
                    this->isIdToken(fieldType);
                }catch(LexicalError error)
                {
                    //emit this->Handle_Error(error);
                }
            }

        }else
            if(tagType == XMLTAGNAME_TYPE_ARRAY)
            {
                QString containtArray = type_element.attribute(XMLATTRIBUTE_ARY_CONTAINT);
                try{
                    this->isIdToken(containtArray);
                }catch(LexicalError error)
                {
                    //emit this->Handle_Error(error);
                }
            }else
                if(tagType == XMLTAGNAME_TYPE_MATRIX)
                {
                    QString containtMat = type_element.attribute(XMLATTRIBUTE_MAT_CONTAINT);
                    try{
                        this->isIdToken(containtMat);
                    }catch(LexicalError error)
                    {
                        //emit this->Handle_Error(error);
                    }
                    QString columns = type_element.attribute(XMLATTRIBUTE_MAT_COLUMNS_C);
                    try{
                        //this->GetConstType(columns);
                    }catch(LexicalError error)
                    {
                        //emit this->Handle_Error(error);
                    }
                    QString rows = type_element.attribute(XMLATTRIBUTE_MAT_ROWS_C);
                    try{
                        //this->Check_NameOFId(rows);
                    }catch(LexicalError error)
                    {
                        //emit this->Handle_Error(error);
                    }
                }else
                    if(tagType == XMLTAGNAME_TYPE_FILE)
                    {
                        QString containtFile = type_element.attribute(XMLATTRIBUTE_FILE_CONTAINT);
                        try{
                            this->isIdToken(containtFile);
                        }catch(LexicalError error)
                        {
                            //emit this->Handle_Error(error);
                        }
                    }
    }

    QDomElement rootvars = root.firstChildElement(XMLTAGNAME_ROOT_VARS);
    QDomNodeList listVars = rootvars.elementsByTagName(XMLTAGNAME_VAR);

    for(int i = 0 ; i < listVars.size();i++)
    {
        QDomElement elmvar = listVars.at(i).toElement();
        QString  var_Id = elmvar.attribute(XMLATTRIBUTE_NAME_ITEM);

        try{
            this->isIdToken(var_Id);
        }catch(LexicalError error)
        {
            //emit this->Handle_Error(error);
        }
        QString  varType = elmvar.attribute(XMLATTRIBUTE_VAR_CONTAINT);
        try{
            this->isIdToken(varType);
        }catch(LexicalError error)
        {
            //emit this->Handle_Error(error);
        }
    }

}

void LexicalAnalyser::StartAnalyse(){

}

void LexicalAnalyser::setStream(QString stream){
    this->stream = stream.trimmed();
}


/*
 * ConstType LexicalAnalyser::GetConstType(QString constvalue)
{
    // ** POSSIBILTE D ' AUGMENTE LA PRECISION D ' ERREUR
    //if(constvalue.isEmpty())
     //   throw LexicalError(Currentlignecode,CurrentColumnlignecode,QString("Valeur du constante attendu "));

    if(constvalue.at(0) == '\"' && constvalue.at(constvalue.size() - 1) == '\"')
        return STRING;
    if(constvalue.at(0) == '\'' && constvalue.at(constvalue.size() - 1) == '\'' && constvalue.size() == 3)
        return CHAR ;

    bool ok;
    constvalue.toInt(&ok);

    if(ok)
        return INTEGER;

    constvalue.toFloat(&ok);

    if(ok)
        return REAL;
    if(constvalue.toUpper() == "VRAI" || constvalue.toUpper() == "FAUX")
        return BOOLEAN;

    //throw LexicalError(Currentlignecode,CurrentColumnlignecode,"Valeur de constante invalide ");
}

 * QStringList listtokns = this->toListTokens(this->stream);
   if( currentIndex++ > listtokns.size())
      return NULL;
   else
   {
       Token * token = new Token();
       token->value = listtokns.at(currentIndex);
       if(listOperators.contains(token->value.toUpper()))
           token->lexeme = Operator;
       else
           if(this->keysWord.contains(token->value.toUpper()))
               token->lexeme = KeyWord;
       else
           {

           }

       return token;
   }

*   Token * token = NULL;
    std::string stream = this->stream.toStdString();
    //while (++currentIndex < stream.size()) {
    if(++currentIndex > stream.size())
        return NULL;
    else
    {
        qDebug()<< stream[currentIndex];
        switch (stream[currentIndex]) {
        case    '"' :
        {
            token = new Token();
            token->value.append('"');
            token->lexeme = Const;
            while (++currentIndex < stream.size() || stream[currentIndex] != '\n') {
                    CurrentColumnlignecode++;
                 token->value.append(stream[currentIndex]);
                 if(stream[currentIndex] == '"')
                     return token;
            }
            // HANDLE ERROR '"' NOT FOUNED !!
            throw "(" + QString::number(this->Currentlignecode).toStdString() + " : " + QString::number(this->CurrentColumnlignecode - 1).toStdString() + " Lexical Error -> '\"' not found ";

        }break;

 // --
        case    '<' :
                     if(stream[currentIndex + 1] == stream[currentIndex + 2] == '-')
                      {
                         token = new Token();
                         token->lexeme = AssignValue;
                         token->value = "<--";
                         currentIndex += 2;
                         return token;

                      }break;

        case    '>' :
                      {
                        token = new Token();
                        token->lexeme = Operator;
                        token->value.append(stream[currentIndex]);
                         if(stream[currentIndex+1] == '=')
                          {
                            token->value.append(stream[++currentIndex]);
                            return token;
                            }
                      }break;

        case    '+' :
        case    '-' :
        case    '*' :
        case    '/' :
        case    '=' : {token = new Token();token->lexeme = Operator;}
// --
        case    '(' : {token = new Token();token->lexeme = Symbol;}
        case    ')' :
        case    '[' :
        case    ']' :
        case    '.' :
        case    ':' :
                        {
                            token->value = QString(stream[currentIndex]);
                            return token;
                        }break;
// --

        case    '\n':
                    {
                        CurrentColumnlignecode = 0;
                        Currentlignecode++;
                    }
        case    '\t':
        case    ' ' :break;

        default:
            if(QChar(stream[currentIndex]).isLetterOrNumber() || stream[currentIndex] == '_')
               {
                token = new Token();
                token->value.append(stream[currentIndex]);
                while ((QChar(stream[currentIndex + 1]).isLetterOrNumber() || stream[currentIndex + 1] == '_') && currentIndex < stream.size()) {
                    CurrentColumnlignecode++;
                    currentIndex++;
                    token->value.append(stream[currentIndex]);
                }
                token->lexeme = NUM_OR_ID;
                return token;
                break;
            }

            else
                throw "(" + QString::number(this->Currentlignecode).toStdString() + " : " + QString::number(this->CurrentColumnlignecode - 1).toStdString() + ") Lexical Error -> invalide token '" + QString(stream[currentIndex]).toStdString() + "'" ;
        }
    }
*/
