#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class InnerjoinCommand : public CommandInterface
{
    public:
    InnerjoinCommand(const std::string& name);
    ~InnerjoinCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};