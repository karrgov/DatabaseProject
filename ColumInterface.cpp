#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "ColumnInterface.h"

ColumnInterface::ColumnInterface(const std::string& name)
{
    this->name = name;
}

std::string ColumnInterface::getName() const
{
    return this->name;
}

ColumnInterface::~ColumnInterface()
{

}