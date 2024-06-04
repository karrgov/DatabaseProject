#include <iostream>
#include <vector>
#include <string>
#include "IntColumn.h"
#include "Converter.h"
#include "Cell.h"
#include "CellInterface.h"

IntColumn::IntColumn(const std::string& name) : ColumnInterface(name)
{

}

IntColumn::~IntColumn()
{
    for(auto i : this->data)
    {
        delete i;
    }
    this->data.clear();
}

std::string IntColumn::getColumnType() const
{
    return "int";
}

std::string IntColumn::valueAt(const unsigned int& index) const
{
    if(index >= this->data.size())
    {
        std::cerr << "Invalid cell index!" << std::endl;
        return "";
    }
    
    if(data[index]->second() == false)
    {
        return "NULL";
    }
    return std::to_string(data[index]->first());
}

std::vector<unsigned int> IntColumn::getIndexesOfCellsWithValues(const std::string& value) const
{
    std::vector<unsigned int> result;

    CellInterface<int>* converted = Converter::toInt(value);

    if(converted->second() == false)
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
        delete converted;
        return result;
    }

    int index = 0;
    for(auto i : this->data)
    {
        if(i->second() == true && i->first() == converted->first())
        {
            result.push_back(index);
        }
        index++;
    }
    delete converted;
    return result;
}

void IntColumn::updateCellByIndex(const unsigned int& index, const std::string& value)
{
    if(index >= this->data.size())
    {
        std::cerr << "Invalid cell index!" << std::endl;
        return;
    }

    CellInterface<int>* converted = Converter::toInt(value);
    this->data[index] = converted;
    //delete converted;
}

void IntColumn::deleteCellByIndex(const unsigned int& index)
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

void IntColumn::insertNewCellWith(const std::string& value)
{
    CellInterface<int>* converted = Converter::toInt(value);
    this->data.push_back(converted);
    //delete converted;
}