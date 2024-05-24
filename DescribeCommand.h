#pragma once 
#include <iostream>
#include "CommandInterface.h"
#include "Catalogue.h"

class DescribeCommand : public CommandInterface
{
    public:
    DescribeCommand(const std::string& name);
    ~DescribeCommand();

    virtual void applyCommand(const std::string& parameters, Catalogue*& database) override;
};