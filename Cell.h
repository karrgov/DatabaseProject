#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "CellInterface.h"

template<typename T>
class Cell : public CellInterface<T>
{
    private:
    T value;
    bool flag;

    public:
    Cell(const T& val, bool otherVal)
    {
        this->value = val;
        this->flag = otherVal;
    }

    T first() const
    {
        return value;
    }

    bool second() const
    {
        return flag;
    }
};