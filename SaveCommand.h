#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class SaveCommand : public CommandInterface
{
    public:
    SaveCommand(const std::string& name);
    ~SaveCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};