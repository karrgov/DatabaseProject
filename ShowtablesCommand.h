#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class ShowtablesCommand : public CommandInterface
{
    ShowtablesCommand(const std::string& name);
    ~ShowtablesCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};