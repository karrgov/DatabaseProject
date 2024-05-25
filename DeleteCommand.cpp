#include "DeleteCommand.h"
#include "Converter.h"
#include "CellInterface.h"
#include "Cell.h"

DeleteCommand::DeleteCommand(const std::string& name) : CommandInterface(name)
{

}

DeleteCommand::~DeleteCommand()
{

}

void DeleteCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while deleting from the database!" << std::endl;
        return;
    }

    std::vector<std::string> parametersConverted;
    Converter::convertLineToParametersList(parameters, parametersConverted);

    if(parametersConverted.size() != 3)
    {
        std::cerr << "Invalid number of arguments for delete command!" << std::endl;
        return;
    }

    CellInterface<int>* converted = Converter::toInt(parametersConverted[1]);

    if(converted->second() == false || converted->first() < 0)
    {
        std::cerr << "Invalid index!" << std::endl;
        return;
    }
    
    database->deleteFuncTable(parametersConverted[0], converted->first(), parametersConverted[2]);

    delete converted;
}