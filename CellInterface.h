/**
 * @file CellInterface.h
 * @author Krasimir
 * @brief This class is an abstract interface for a collection of derived classes. This design allows the use of a std::vector of pointers to objects that inherit from it, enabling polymorphic behavior.
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <iostream>
#include <vector>
#include <string>

template<class T>
class CellInterface
{
    public:
    virtual ~CellInterface()
    {
        
    }

    virtual const T& first() const = 0;
    virtual void setFirst(const T& value) = 0;
    virtual bool second() const = 0;
    virtual void setSecond(bool value) = 0;
};