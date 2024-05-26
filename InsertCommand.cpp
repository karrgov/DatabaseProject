#include "InsertCommand.h"
#include "Converter.h"
#include "CellInterface.h"
#include "Cell.h"

InsertCommand::InsertCommand(const std::string& name) : CommandInterface(name)
{

}

InsertCommand::~InsertCommand()
{

}

void InsertCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while inserting into the specific table in the database!" << std::endl;
        std::cout << std::endl;
        return;
    }

    std::vector<std::string> parametersConverted;
    Converter::convertLineToParametersList(parameters, parametersConverted);

    std::string name = parametersConverted[0];

    for(int i = 1; i < parametersConverted.size(); i++)
    {
        parametersConverted[i - 1] = parametersConverted[i];
    }
    parametersConverted.pop_back();

    
    database->insertInTable(name, parametersConverted);
    std::cout << "Insert completed!" << std::endl;
    std::cout << std::endl;
}