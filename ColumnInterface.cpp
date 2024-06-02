/**
 * @file ColumnInterface.cpp
 * @author Krasimir
 * @brief This class is an abstract interface for a collection of derived classes. This design allows the use of a std::vector of pointers to objects that inherit from it, enabling polymorphic behavior.
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <string>
#include "ColumnInterface.h"

/**
 * @brief Construct a new Column Interface:: Column Interface object
 * 
 * @param name 
 */
ColumnInterface::ColumnInterface(const std::string& name)
{
    this->name = name;
}

/**
 * @brief Returns the name of the column
 * 
 * @return std::string 
 */
std::string ColumnInterface::getName() const
{
    return this->name;
}

/**
 * @brief Destroy the Column Interface:: Column Interface object
 * 
 */
ColumnInterface::~ColumnInterface()
{

}