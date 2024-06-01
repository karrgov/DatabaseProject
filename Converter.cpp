/**
 * @file Converter.cpp
 * @author Krasimir
 * @brief This class makes the conversion of std::string to the desired types possible, supported by the program. Static member functions in order to be called without an object of the class
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <string>
#include "Converter.h"
#include "Cell.h"
#include "CellInterface.h"

CellInterface<int>* Converter::toInt(const std::string& value)
{
    CellInterface<int>* defaultCell = new Cell<int>(0, false);

    if(value.size() == 0)
    {
        return defaultCell;
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
            return defaultCell;
        }
    }

    if(in == false)
    {
        return defaultCell;
    }

    if(isNegative)
    {
        result = result * (-1);
    }
    else
    {
        result = result * 1;
    }

    delete defaultCell;

    CellInterface<int>* final = new Cell<int>(result, true);
    return final;
}

CellInterface<double>* Converter::toDouble(const std::string& value)
{
    CellInterface<double>* defaultCell = new Cell<double>(0, false);

    if(value.size() == 0)
    {
        return defaultCell;
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

    double result = 0;
    bool in = false;

    for(int i = start; i < value.size(); i++)
    {
        char current = value[i];

        if(current >= '0' && current <= '9')
        {
            in = true;
            result = result * 10 + current - '0';
        }
        else if(current == '.')
        {
            int step = 10;
            bool newIn = false;

            for(int j = i + 1; j < value.size(); ++j) 
            {
                if(value[j] >= '0' && value[j] <= '9') 
                {
                    newIn = true;
                    result = result + (value[j] - '0') * 1.0 / step;
                    step *= 10;
                }
                else 
                {
                    return defaultCell;
                }
            }
            if(!newIn) 
            {
                return defaultCell;
            }

            break;
        }
        else 
        {
        return defaultCell;
        }
    }

    if(!in) 
    {
        return defaultCell;
    }

    if(isNegative)
    {
        result = result * (-1);
    }
    else
    {
        result = result * 1;
    }

    delete defaultCell;

    CellInterface<double>* final = new Cell<double>(result, true);
    return final;
}
    

bool Converter::isString(const std::string& value)
{
    if(value.size() >= 2 & value[0] == '"' && value[value.size() - 1] == '"')
    {
        return true;
    }
    return false;
}

bool Converter::isNull(const std::string& value)
{
    if(value == "NULL")
    {
        return true;
    }
    return false;
}

void Converter::convertLineToParametersList(const std::string& line, std::vector<std::string>& parameters)
{
    parameters.clear();
    std::string currentParameter;

    bool startedString = false;

    for(int i = 0; i < line.size(); i++)
    {
        if(line[i] == ' ')
        {
            if(startedString == true)
            {
                currentParameter = currentParameter + line[i];
            }
            else
            {
                if(currentParameter.size() > 0)
                {
                    parameters.push_back(currentParameter);
                }
                currentParameter = "";
            }
        }
        else if(line[i] == '"')
        {
            if(i > 0 && line[i - 1] == '\\') 
            {
                currentParameter.pop_back();
                currentParameter += line[i];
            } 
            else if(startedString == true) 
            {
                startedString = false;

                currentParameter += line[i];
                parameters.push_back(currentParameter);
                currentParameter = "";
            }
            else 
            {
                startedString = true;
                currentParameter = currentParameter + line[i];
            }
        }
        else
        {
            currentParameter = currentParameter + line[i];
        }
    }
    if(currentParameter.size() > 0)
    {
        parameters.push_back(currentParameter);
    }
}
