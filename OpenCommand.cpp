#include "OpenCommand.h"

OpenCommand::OpenCommand(const std::string& name) : CommandInterface(name)
{

}

OpenCommand::~OpenCommand()
{

}

void OpenCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database != nullptr)
    {
        std::cerr << "Error while opening the database!" << std::endl;
        return;
    }

    database = new Catalogue(parameters);
    std::cout << "Database successfuly opened!" << std::endl;
    std::cout << std::endl;
}