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

    T& first() const override
    {
        return value;
    }

    bool second() const override
    {
        return flag;
    }

    void setSecond(bool value) override
    {
        this->flag = value;
    }
};