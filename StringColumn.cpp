#include <iostream>
#include <vector>
#include <string>
#include "StringColumn.h"
#include "Converter.h"
#include "Cell.h"
#include "CellInterface.h"

StringColumn::StringColumn(const std::string& name) : ColumnInterface(name)
{
    
}

StringColumn::~StringColumn()
{
    for(auto i : this->data)
    {
        delete i;
    }
    this->data.clear();
}

std::string StringColumn::getColumnType() const
{
    return "string";
}

std::string StringColumn::valueAt(const unsigned int& index) const
{
    if(index >= this->data.size())
    {
        std::cerr << "Invalid cell index!" << std::endl;
        return;
    }

    if(data[index]->second() == false)
    {
        return "NULL";
    }
    return data[index]->first();
}

std::vector<unsigned int> StringColumn::getIndexesOfRowsWithValues(const std::string& value) const
{
    std::vector<unsigned int> result;

    if(Converter::isString(value) == false)
    {
        if(Converter::isNull(value) == true)
        {
            int index = 0;

            for(auto i : this->data)
            {
                if(i->second() == false)
                {
                    result.push_back(index);
                }
                index++;
            }
        }
        return result;
    }

    int index = 0;
    for(auto i : this->data)
    {
        if(i->second() == true && i->first() == value)
        {
            result.push_back(index);
        }
        index++;
    }
    return result;
}

void StringColumn::updateRowByIndex(const unsigned int& index, const std::string& value)
{
    if(index >= this->data.size())
    {
        std::cerr << "Invalid cell index!" << std::endl;
        return;
    }

    if(Converter::isString(value) == true) 
    {
        this->data[index]->first() = value;
        this->data[index]->setSecond(true);
    } 
    else if(Converter::isNull(value) == true) 
    {
        this->data[index]->setSecond(false);
    } 
}

void StringColumn::deleteRowByIndex(const unsigned int& index)
{
    if(index >= this->data.size())
    {
        std::cerr << "Invalid cell index!" << std::endl;
        return;
    }
    
    for(int i = index + 1; i < this->data.size(); ++i)
    {
        this->data[i - 1] = this->data[i];
    }
    this->data.pop_back();
}

void StringColumn::insertNewRowWith(const std::string& value)
{
    if(Converter::isString(value) == true) 
    {
        CellInterface<std::string>* final = new Cell<std::string>(value, true);
        this->data.push_back(final);
    } 
    else if(Converter::isNull(value) == true) 
    {
        CellInterface<std::string>* final = new Cell<std::string>("", false);
        this->data.push_back(final);
    } 
}