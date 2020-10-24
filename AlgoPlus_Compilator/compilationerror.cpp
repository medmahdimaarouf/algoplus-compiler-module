#include "compilationerror.h"

CompilationError::CompilationError()
{
}

CompilationError::CompilationError(int lignecode, int columLigne)
{
    setLigneCode(lignecode);
    setcolumnLigne(columLigne);
}

CompilationError::CompilationError(StdString description)
{
    setDescription(description);
}

CompilationError::CompilationError(int lignecode, StdString description)
{
    this->description = description;
    this->ligneCode = lignecode;
}

CompilationError::CompilationError(int lignecode, int columLigne, StdString description)
{
    this->ligneCode = lignecode;
    this->columnLigne = columLigne;
    this->description = description;
}

void CompilationError::setLigneCode(int lignecode)
{
    this->ligneCode = lignecode;
}

void CompilationError::setcolumnLigne(int columnLigne)
{
    this->columnLigne = columnLigne;
}

unsigned int CompilationError::getLigneCode()
{
    return this->ligneCode;
}

StdString CompilationError::getDescription()
{
    return this->description;
}

unsigned int CompilationError::getcolumnLigne()
{
    return this->columnLigne;
}

void CompilationError::setDescription(StdString description)
{
    this->description = description;
}

StdString CompilationError::toString()
{
    return "( Ligne : " + StdString::number(ligneCode) + ", Colonne : " + StdString::number(columnLigne - 1) + " )Compilation error -> " + description;
}
