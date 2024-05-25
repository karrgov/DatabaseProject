#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class UpdateCommand : public CommandInterface
{
    public:
    UpdateCommand(const std::string& name);
    ~UpdateCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};