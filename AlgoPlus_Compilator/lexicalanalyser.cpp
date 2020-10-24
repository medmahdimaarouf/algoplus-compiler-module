#include "lexicalanalyser.h"


int unsigned LexicalAnalyser::Currentlignecode = 1;
int unsigned LexicalAnalyser::CurrentColumnlignecode = 1;

std::list<StdString> listAlgoKeyWords;
std::list<StdString> listJsKeyWords;

LexicalAnalyser::LexicalAnalyser()
{
    if(listAlgoKeyWords.empty()){
        listAlgoKeyWords.push_back("ALGORITHME");
        listAlgoKeyWords.push_back("CONSTANTES");
        listAlgoKeyWords.push_back("TYPES");
        listAlgoKeyWords.push_back("ENREGISTREMENT");
        listAlgoKeyWords.push_back("FICHIER");
        listAlgoKeyWords.push_back("TABLEAU");
        listAlgoKeyWords.push_back("VARIABLES");
        listAlgoKeyWords.push_back("FONCTION");
        listAlgoKeyWords.push_back("PROCEDURE");
        listAlgoKeyWords.push_back("DEBUT");
        listAlgoKeyWords.push_back("POUR");
        listAlgoKeyWords.push_back("SI");
        listAlgoKeyWords.push_back("SELON");
        listAlgoKeyWords.push_back("TANTEQUE");
        listAlgoKeyWords.push_back("REPETER");
        listAlgoKeyWords.push_back("JUSQU_A");
        listAlgoKeyWords.push_back("FN");
        listAlgoKeyWords.push_back("NON");
        listAlgoKeyWords.push_back("ET");
        listAlgoKeyWords.push_back("OU");
        listAlgoKeyWords.push_back("MOD");
        listAlgoKeyWords.push_back("DIV");
        listAlgoKeyWords.push_back("NIL");
        listAlgoKeyWords.push_back("NULLE");
        listAlgoKeyWords.push_back("FIN");
        listAlgoKeyWords.push_back("DANS");
        listAlgoKeyWords.push_back("VRAI");
        listAlgoKeyWords.push_back("FAUX");
        listAlgoKeyWords.push_back("RETOURNER");
        listAlgoKeyWords.push_back("FAIRE");
        listAlgoKeyWords.push_back("SI_NON");
        listAlgoKeyWords.push_back("SINON");
    }

    if(listJsKeyWords.empty()){
        listJsKeyWords.push_back("var");
        listJsKeyWords.push_back("function");
        listJsKeyWords.push_back("throw");
        listJsKeyWords.push_back("try");
        listJsKeyWords.push_back("return");
        listJsKeyWords.push_back("catch");
        listJsKeyWords.push_back("break");
        listJsKeyWords.push_back("continue");
        listJsKeyWords.push_back("goto");
        listJsKeyWords.push_back("delete");
    }

    this->currentIndex = 0;
    this->Currentlignecode = this->CurrentColumnlignecode = 1;
    this->currentToken = lastToken = NULL;
}

Token * LexicalAnalyser::NextToken()
{
    this->lastToken = this->currentToken;

    Token * token = NULL;
    if(currentIndex >= 0)
    {
        token = new Token(Currentlignecode,CurrentColumnlignecode,currentIndex,currentToken);
        switch (stream[currentIndex].toLatin1()) {
        case    '\"':{
            token->setNature(STR);
            token->setValue(str());
        }break;
        case    '\'':{
            token->setNature(CHAR);
            token->setValue(chr());
        }break;
 // --
        case    '<' :if( lookAhead(3) == "<--"){token->setNature(AssignValue);token->setValue(Advance(3)); break;  }
              else   if( lookAhead(2) == "<>"){token->setNature(LogicOperator);token->setValue(Advance(2)); break; }
        case    '>' :if(lookAhead(2)[1] == '='){token->setNature(LogicOperator);token->setValue(Advance(2)); break;}
        case    '=' :token->setNature(LogicOperator);
        case    '+' :
        case    '-' :

        case    '*' :
        case    '/' :{
                        token->setValue(StdString(stream[currentIndex]));
                        token->setNature(ArithmeticOperator);
                        Advance();
                    }break;

        case    '(' :token->setNature(Lp);
        case    ')' :token->setNature(Rp);
        case    '[' :token->setNature(LI);
        case    ']' :token->setNature(RI);
        case    ',' :token->setNature(Punctuation);
        case    '.' :if(lookAhead(2) == ".."){token->setNature(Punctuation);token->setValue(Advance(2));break;}
                     else token->setNature(Punctuation);
        case    '@' :token->setNature(LocationSpecifier);

        case    ':' :{
                        token->setNature(AssignType);
                        token->setValue(StdString(stream[currentIndex]));
                        Advance();
                    }break;
// --
        case    '\n':
        case    ' ' :
        case    '\r':
        case    '\t': {
                        deleteBlanks();
                        delete token;
                        token =  NextToken();
        } break;
        case    '{':{
            IngioreComment();
            delete token;
            token = NextToken();
        }break;
        default:
            if(stream[currentIndex].isDigit()){
                NumberT:
                    {
                        bool reel;
                        token->setValue(Number(&reel));
                        if(reel)
                            token->setNature(Reel);
                        else
                            token->setNature(NUMBER);
                    }
            }
            else
                if(stream[currentIndex].isLetter() || stream[currentIndex] == '_')
                {
                    token->setValue(Id());
                    if(std::find(listAlgoKeyWords.begin(),listAlgoKeyWords.end(),token->Value().toUpper()) == listAlgoKeyWords.end())
                        token->setNature(ID);
                    else
                        token->setNature(KeyWord);
                }
            else
                {
                    delete token;
                    throw LexicalError(Currentlignecode,CurrentColumnlignecode," Caractere illegal '" + StdString(stream[currentIndex]) + "'") ;
                }

        }

        token->setEndIndex(currentIndex);
    }

    currentToken = token;
    if(currentToken)currentToken->setBackToken(lastToken);
    return token;
}

Token *LexicalAnalyser::BackToken()
{
    if(lastToken){
        SeekToken(lastToken);
    }else{
        currentToken = NULL;
        LexicalAnalyser();
    }
    return currentToken;
}

Token * LexicalAnalyser::SeekToken(Token *token)
{
    if(token){

        this->currentIndex = token->getEndIndex();
        this->Currentlignecode = token->getLineNumber();
        this->CurrentColumnlignecode = token->getColumnNumber() + token->Value().size();

        this->currentToken = token;
        this->lastToken = token->getBackToken();
    }

    return currentToken;
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

void LexicalAnalyser::deleteBlanks()
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

StdString LexicalAnalyser::Number(bool *reel)
{
    StdString number = "";
    *reel = false;
    while (currentIndex != -1 && stream[currentIndex].isDigit()) {
        number.append(stream[currentIndex]);
        Advance();
    }
    StdString look = lookAhead(2);
    if(look.size() == 2)
    {
        if(look[1].isNumber() && look[0] == '.')
          {
            number.append(".");
            Advance();
            while (currentIndex != -1 && stream[currentIndex].isDigit()) {
                number.append(stream[currentIndex]);
                Advance();
            }
            *reel = true;
          }
    }
    return number;
}

StdString LexicalAnalyser::Id()
{
    StdString id = "";
    while (currentIndex != -1 && (this->stream[currentIndex].isLetterOrNumber() || this->stream[currentIndex] == '_')) {
        id.append(stream[currentIndex]);
        Advance();
    }

    return id;
}

StdString LexicalAnalyser::str()
{
    StdString str = "\"";
    Advance();
    while (currentIndex != -1 && stream.at(currentIndex) != '\"' && stream.at(currentIndex) != '\n') {
        str.append(stream[currentIndex]);
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

StdString LexicalAnalyser::chr()
{
    StdString chr = "\'";
    Advance();
    if(currentIndex != -1)
    {
        if(stream[currentIndex] == '\\')
        {
            chr.append("\\");
            Advance();
            switch (stream[currentIndex].toLatin1()) {
            case 'n' :
            case 'r' :
            case 't' :
            case '"' :
            case '\'':{
                chr.append(stream[currentIndex]);
                Advance();
                if(stream[currentIndex] == '\'')
                {
                    chr.append("'");
                    Advance();
                    return chr;
                }
            }
            default:
                throw LexicalError(Currentlignecode,CurrentColumnlignecode," Signfication erroné < " + StdString(stream[currentIndex]) + "\>");
            }
        }else
        {
            chr.append(StdString(stream[currentIndex]));
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

StdString LexicalAnalyser::Advance(const int nbc)
{
    StdString string = lookAhead(nbc);
    for (int i = 0;currentIndex != -1 && i < nbc;i++){
        Advance();
    }
    return string;
}

StdString LexicalAnalyser::lookAhead(const int nbc)const
{
    return stream.mid(currentIndex,nbc);

}

bool LexicalAnalyser::isIdToken(const StdString token) {

    if(token.isEmpty())return false;
    if(!token[0].isLetter() && token[token.size()-1] != '_' || token.count(' ') != 0)
        return false;
    foreach (QChar c, token) {
        if(c.isSymbol() && c != '_')
            return false;
    }

    return true;
}

Token *LexicalAnalyser::lookAhead()
{
    Token * token = NextToken();
    BackToken();
    return token;
}
Token *LexicalAnalyser::getCurrentToken() const
{
    return currentToken;
}
Token *LexicalAnalyser::getLastToken() const
{
    return lastToken;
}

void LexicalAnalyser::StartAnalyse(){

}

StdString LexicalAnalyser::setStream(const StdString stream){

    this->stream = stream.trimmed();
    LexicalAnalyser();
    return this->stream;
}
