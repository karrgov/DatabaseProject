#include "DescribeCommand.h"

DescribeCommand::DescribeCommand(const std::string& name) : CommandInterface(name)
{

}

DescribeCommand::~DescribeCommand()
{

}

void DescribeCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while showing the tables from the database!" << std::endl;
        return;
    }

    database->describeTable(parameters);
}