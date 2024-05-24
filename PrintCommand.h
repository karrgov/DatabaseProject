#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class PrintCommand : public CommandInterface
{
    public:
    PrintCommand(const std::string& name);
    ~PrintCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};