#include "SelectCommand.h"
#include "Converter.h"
#include "CellInterface.h"
#include "Cell.h"

SelectCommand::SelectCommand(const std::string& name) : CommandInterface(name)
{

}

SelectCommand::~SelectCommand()
{

}

void SelectCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while selecting from the database!" << std::endl;
        return;
    }

    std::vector<std::string> parametersConverted;
    Converter::convertLineToParametersList(parameters, parametersConverted);

    if(parametersConverted.size() != 3)
    {
        std::cerr << "Invalid number of arguments for select command!" << std::endl;
        return;
    }

    CellInterface<int>* converted = Converter::toInt(parametersConverted[0]);

    if(converted->second() == false || converted->first() < 0)
    {
        std::cerr << "Invalid index!" << std::endl;
        return;
    }
    
    database->selectFromTable(parametersConverted[2], converted->first(), parametersConverted[1]);

    delete converted;
}