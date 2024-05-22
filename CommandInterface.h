#pragma once
#include <iostream>
#include <vector>
#include "Catalogue.h"

class CommandInterface
{
    private:
    std::string nameOfCommand;

    public:
    CommandInterface(const std::string& name);
    virtual ~CommandInterface();
    const std::string& getCommandName() const;

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) = 0;
};