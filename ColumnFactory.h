#pragma once
#include <iostream>
#include "ColumnInterface.h"

class ColumnFactory
{
    public: 
    static ColumnInterface* createColumn(const std::string& name, const std::string& type);
};