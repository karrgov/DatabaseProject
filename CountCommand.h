#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class CountCommand : public CommandInterface
{
    public:
    CountCommand(const std::string& name);
    ~CountCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};