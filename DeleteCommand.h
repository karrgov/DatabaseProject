#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class DeleteCommand : public CommandInterface
{
    public:
    DeleteCommand(const std::string& name);
    ~DeleteCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};