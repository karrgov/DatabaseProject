#include "RenameCommand.h"
#include "Converter.h"
#include "CellInterface.h"
#include "Cell.h"

RenameCommand::RenameCommand(const std::string& name) : CommandInterface(name)
{

}

RenameCommand::~RenameCommand()
{

}

void RenameCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while renaming the specific table in the database!" << std::endl;
        return;
    }

    std::vector<std::string> parametersConverted;
    Converter::convertLineToParametersList(parameters, parametersConverted);

    if(parametersConverted.size() != 2)
    {
        std::cerr << "Invalid number of arguments for rename command!" << std::endl;
        return;
    }
    
    database->renameTable(parametersConverted[0], parametersConverted[1]);
}