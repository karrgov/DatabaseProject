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