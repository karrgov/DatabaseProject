#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class SelectCommand : public CommandInterface
{
    public:
    SelectCommand(const std::string& name);
    ~SelectCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};