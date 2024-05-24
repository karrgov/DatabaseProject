#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class ImportCommand : public CommandInterface
{
    ImportCommand(const std::string& name);
    ~ImportCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};