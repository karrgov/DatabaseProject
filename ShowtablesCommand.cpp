#include "ShowtablesCommand.h"
#include "Converter.h"

ShowtablesCommand::ShowtablesCommand(const std::string& name) : CommandInterface(name)
{

}

ShowtablesCommand::~ShowtablesCommand()
{

}

void ShowtablesCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while showing the tables from the database!" << std::endl;
        std::cout << std::endl;
        return;
    }

    database->showAllTables();
}