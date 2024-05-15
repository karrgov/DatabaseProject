#include <iostream>
#include <vector>
#include <string>
#include "DoubleColumn.h"
#include "Converter.h"
#include "Cell.h"
#include "CellInterface.h"

DoubleColumn::DoubleColumn(const std::string& name) : ColumnInterface(name)
{

}

std::string DoubleColumn::getColumnType() const
{
    return "double";
}

std::string DoubleColumn::valueAt(const unsigned int& index) const
{
    if(data[index]->second() == false)
    {
        return "NULL";
    }
    return std::to_string(data[index]->first());
}

std::vector<unsigned int> DoubleColumn::getIndexesOfRowsWithValues(const std::string& value) const
{

}

void DoubleColumn::updateRowByIndex(const unsigned int& index, const std::string& newValue)
{

}

void DoubleColumn::deleteRowByIndex(const unsigned int& index)
{

}
 
void DoubleColumn::insertNewRowWith(const std::string& value)
{
    
}