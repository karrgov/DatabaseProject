/**
 * @file ColumnFactory.cpp
 * @author Krasimir
 * @brief This class implements the factory design pattern and is responsible for creating column objects depending on the provided type
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
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
