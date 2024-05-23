#include "SaveCommand.h"

SaveCommand::SaveCommand(const std::string& name) : CommandInterface(name)
{

}

SaveCommand::~SaveCommand()
{

}

void SaveCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while saving the database!" << std::endl;
    }

    database->saveCatalogueToDefaultFile();
}