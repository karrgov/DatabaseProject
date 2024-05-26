#include "AddcolumnCommand.h"
#include "Converter.h"
#include "CellInterface.h"
#include "Cell.h"

AddcolumnCommand::AddcolumnCommand(const std::string& name) : CommandInterface(name)
{

}

AddcolumnCommand::~AddcolumnCommand()
{

}

void AddcolumnCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while adding a column to the table!" << std::endl;
        std::cout << std::endl;
        return;
    }

    std::vector<std::string> parametersConverted;
    Converter::convertLineToParametersList(parameters, parametersConverted);

    if(parametersConverted.size() != 3)
    {
        std::cerr << "Invalid number of arguments for addcolumn command!" << std::endl;
        std::cout << std::endl;
        return;
    }
    
    database->addColumnToTable(parametersConverted[0], parametersConverted[1], parametersConverted[2]);
    std::cout << "Column added!" << std::endl;
    std::cout << std::endl;
}