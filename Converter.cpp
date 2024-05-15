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

        delete wrong;

        return new Cell<int>(result, true);
    }

    CellInterface<double>* Converter::toDouble(const std::string& value)
    {
        CellInterface<double>* wrong = new Cell<double>(0, false);

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
                        return wrong;
                    }
                }
                if(!newIn) 
                {
                    return wrong;
                }

                break;
            }
            else 
            {
            return wrong;
            }
        }

        if(!in) 
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

        delete wrong;

        return new Cell<double>(result, true);
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

    void Converter::parseLineToParam(const std::string& line, std::vector<std::string>& parameters)
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
