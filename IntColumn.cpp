#include <iostream>
#include <vector>
#include <string>
#include "IntColumn.h"

IntColumn::IntColumn(const std::string& name) : ColumnInterface(name)
{

}

std::string IntColumn::getColumnType() const
{
    return "int";
}

std::string IntColumn::valueAt(const unsigned int& index) const
{
    if(data[index].second == false)
    {
        return "NULL";
    }
    return std::to_string(data[index].first);
}

std::vector<unsigned int> IntColumn::getIndexesOfRowsWithValues(const std::string& value) const
{
    std::vector<unsigned int> result;

    

}

void IntColumn::updateRowByIndex(const unsigned int& index, const std::string& newValue)
{

}

void IntColumn::deleteRowByIndex(const unsigned int& index)
{

}

void IntColumn::insertNewRowWith(const std::string& value)
{

}