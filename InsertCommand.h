#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class InsertCommand : public CommandInterface
{
    public:
    InsertCommand(const std::string& name);
    ~InsertCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};