#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class RenameCommand : public CommandInterface
{
    public:
    RenameCommand(const std::string& name);
    ~RenameCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};