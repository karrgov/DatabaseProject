#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class ExportCommand : public CommandInterface
{
    public:
    ExportCommand(const std::string& name);
    ~ExportCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};