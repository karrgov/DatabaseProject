/**
 * @file CommandInterface.cpp
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
#include "Catalogue.h"
#include "CommandInterface.h"

/**
 * @brief Construct a new Command Interface:: Command Interface object
 * 
 * @param name 
 */
CommandInterface::CommandInterface(const std::string& name)
{
    this->nameOfCommand = name;
}

/**
 * @brief Destroy the Command Interface:: Command Interface object
 * 
 */
CommandInterface::~CommandInterface()
{

}

/**
 * @brief Returns the name of the command 
 * 
 * @return const std::string& 
 */
const std::string& CommandInterface::getCommandName() const
{
    return this->nameOfCommand;
}
