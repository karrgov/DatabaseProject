#include "CloseCommand.h"

CloseCommand::CloseCommand(const std::string& name) : CommandInterface(name)
{

}

CloseCommand::~CloseCommand()
{

}

void CloseCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while closing the database!" << std::endl;
        return;
    }

    delete database;
    database = nullptr;
}
