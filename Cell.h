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
    Cell(const T& val, bool otherVal)
    {
        this->value = val;
        this->flag = otherVal;
    }

    const T& first() const override
    {
        return value;
    }

    void setFirst(const T& value) override
    {
        this->value = value;
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