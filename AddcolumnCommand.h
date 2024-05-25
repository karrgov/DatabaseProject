#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class AddcolumnCommand : public CommandInterface
{
    public:
    AddcolumnCommand(const std::string& name);
    ~AddcolumnCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};