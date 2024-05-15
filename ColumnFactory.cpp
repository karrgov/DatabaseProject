#include <iostream>
#include "ColumnFactory.h"
#include "IntColumn.h"
#include "DoubleColumn.h"
#include "StringColumn.h"

ColumnInterface* ColumnFactory::createColumn(const std::string& name, const std::string& type)
{
    if(type == "int")
    {
        return new IntColumn(name);
    }
    
    if(type == "double")
    {
        return new DoubleColumn(name);
    }

    if(type == "string")
    {
        return new StringColumn(name);
    }

    return nullptr;
}
