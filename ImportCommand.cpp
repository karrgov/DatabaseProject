#include "ImportCommand.h"
#include "Converter.h"

ImportCommand::ImportCommand(const std::string& name) : CommandInterface(name)
{

}

ImportCommand::~ImportCommand()
{

}

void ImportCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while importing to the database!" << std::endl;
        std::cout << std::endl;
        return;
    }

    std::vector<std::string> parametersConverted;
    Converter::convertLineToParametersList(parameters, parametersConverted);

    if(parametersConverted.size() != 2)
    {
        std::cerr << "Invalid number of arguments for import command!" << std::endl;
        std::cout << std::endl;
        return;
    }

    database->importTableFromFile(parametersConverted[0], parametersConverted[1]);
    std::cout << "Table imported from the file!" << std::endl;
    std::cout << std::endl;
}