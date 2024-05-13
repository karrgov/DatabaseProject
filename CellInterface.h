#pragma once
#include <iostream>
#include <vector>
#include <string>

template<typename T>
class CellInterface
{
    public:
    virtual ~CellInterface();

    virtual T first() const = 0;
    virtual bool seocnd() const = 0;
};