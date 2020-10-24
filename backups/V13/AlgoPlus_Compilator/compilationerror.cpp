#include "compilationerror.h"

CompilationError::CompilationError()
{
}

CompilationError::CompilationError(int lignecode, int columLigne)
{
    setLigneCode(lignecode);
    setcolumnLigne(columLigne);
}

CompilationError::CompilationError(std::string description)
{
    setDescription(description);
}

CompilationError::CompilationError(int lignecode, std::string description)
{
    this->description = description;
    this->ligneCode = lignecode;
}

CompilationError::CompilationError(int lignecode, int columLigne, std::string description)
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

std::string CompilationError::getDescription()
{
    return this->description;
}

unsigned int CompilationError::getcolumnLigne()
{
    return this->columnLigne;
}

void CompilationError::setDescription(std::string description)
{
    this->description = description;
}

std::string CompilationError::toString()
{
    return "( Ligne : " + Number(ligneCode) + ", Colonne : " + Number(columnLigne - 1) + " )Compilation error -> " + description;
}
