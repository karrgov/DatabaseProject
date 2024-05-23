#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class SaveAsCommand : public CommandInterface
{
    SaveAsCommand(const std::string& name);
    ~SaveAsCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};