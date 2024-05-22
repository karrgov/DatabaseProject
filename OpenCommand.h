#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class OpenCommand : public CommandInterface
{
    public:
    OpenCommand(const std::string& name);
    ~OpenCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};