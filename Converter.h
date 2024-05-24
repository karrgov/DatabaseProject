#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "CellInterface.h"

class Converter
{
    public:
    static CellInterface<int>* toInt(const std::string& value);
    static CellInterface<double>* toDouble(const std::string& value);
    static bool isString(const std::string& value);
    static bool isNull(const std::string& value);

    static void convertLineToParametersList(const std::string& line, std::vector<std::string>& parameters);
};