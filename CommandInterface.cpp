#include <iostream>
#include <vector>
#include "Catalogue.h"
#include "CommandInterface.h"

CommandInterface::CommandInterface(const std::string& name)
{
    this->nameOfCommand = name;
}

CommandInterface::~CommandInterface()
{

}

const std::string& CommandInterface::getCommandName() const
{
    return this->nameOfCommand;
}
