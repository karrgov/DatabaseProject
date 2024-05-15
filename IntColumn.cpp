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

std::string IntColumn::getColumnType() const
{
    return "int";
}

std::string IntColumn::valueAt(const unsigned int& index) const
{
    if(data[index]->second() == false)
    {
        return "NULL";
    }
    return std::to_string(data[index]->first());
}

std::vector<unsigned int> IntColumn::getIndexesOfRowsWithValues(const std::string& value) const
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

void IntColumn::updateRowByIndex(const unsigned int& index, const std::string& value)
{
    CellInterface<int>* converted = Converter::toInt(value);
    this->data[index] = converted;
    delete converted;
}

void IntColumn::deleteRowByIndex(const unsigned int& index)
{
    for(int i = 0; i < this->data.size(); ++i)
    {
        this->data[i - 1] = this->data[i];
    }
    this->data.pop_back();
}

void IntColumn::insertNewRowWith(const std::string& value)
{
    CellInterface<int>* converted = Converter::toInt(value);
    this->data.push_back(converted);
    delete converted;
}