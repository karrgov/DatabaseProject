#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class AggregateCommand : public CommandInterface
{
    public:
    AggregateCommand(const std::string& name);
    ~AggregateCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};