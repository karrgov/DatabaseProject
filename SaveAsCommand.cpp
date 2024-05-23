#include "SaveAsCommand.h"

SaveAsCommand::SaveAsCommand(const std::string& name) : CommandInterface(name)
{

}

SaveAsCommand::~SaveAsCommand()
{

}

void SaveAsCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while saving the database to a specific file!" << std::endl;
        return;
    }

    database->saveCatalogueToDifferentFile(parameters);
}