#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class CloseCommand : public CommandInterface
{
    public:
    CloseCommand(const std::string& name);
    ~CloseCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};