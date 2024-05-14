#include <iostream>
#include <vector>
#include <string>
#include "Converter.h"
#include "Cell.h"
#include "CellInterface.h"

    CellInterface<int>* Converter::toInt(const std::string& value)
    {
        CellInterface<int>* wrong = new Cell<int>(0, false);

        if(value.size() == 0)
        {
            return wrong;
        }

        int start = 0;
        bool isNegative = false;

        if(value[0] == '+')
        {
            start++;
        }
        else if(value[0] == '-')
        {
            start++;
            isNegative = true;
        }

        int result = 0;
        bool in = false;

        for(int i = start; i < value.size(); i++)
        {
            char current = value[i];

            if(current >= '0' && current <= '9')
            {
                in = true;
                result = result * 10 + current - '0';
            }
            else
            {
                return wrong;
            }
        }

        if(in == false)
        {
            return wrong;
        }

        if(isNegative)
        {
            result = result * (-1);
        }
        else
        {
            result = result * 1;
        }
        
        return new Cell<int>(result, true);
    }

    CellInterface<double>* Converter::toDouble(const std::string& value)
    {

    }

    bool Converter::isString(const std::string& value)
    {

    }

    bool Converter::isNull(const std::string& value)
    {

    }

    void Converter::parseLineToParam(const std::string& line, std::vector<std::string>& parameters)
    {

    }
