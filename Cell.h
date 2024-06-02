/**
 * @file Cell.h
 * @author Krasimir
 * @brief This is a template class that inherits from the CellInterface
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
#include "CellInterface.h"

template<class T>
class Cell : public CellInterface<T>
{
    private:
    T value;
    bool flag;

    public:
    /**
     * @brief Construct a new Cell object
     * 
     * @param val 
     * @param otherVal 
     */
    Cell(const T& val, bool otherVal)
    {
        this->value = val;
        this->flag = otherVal;
    }

    /**
     * @brief Returns the value of the cell 
     * 
     * @return const T& 
     */
    const T& first() const override
    {
        return value;
    }

    /**
     * @brief Sets the value of the cell
     * 
     * @param value 
     */
    void setFirst(const T& value) override
    {
        this->value = value;
    }

    /**
     * @brief Returns the bool value of the cell
     * 
     * @return true 
     * @return false 
     */
    bool second() const override
    {
        return flag;
    }

    /**
     * @brief Sets the bool value of the cell 
     * 
     * @param value 
     */
    void setSecond(bool value) override
    {
        this->flag = value;
    }
};