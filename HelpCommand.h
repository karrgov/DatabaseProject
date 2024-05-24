#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class HelpCommand : public CommandInterface
{
    public:
    HelpCommand(const std::string& name);
    ~HelpCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};