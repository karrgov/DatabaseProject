#pragma once
#include <iostream>
#include <vector>
#include <string>

template<typename T>
class CellInterface
{
    public:
    virtual ~CellInterface()
    {
        
    }

    virtual const T& first() const = 0;
    virtual bool second() const = 0;
    virtual void setSecond(bool value) = 0;
};