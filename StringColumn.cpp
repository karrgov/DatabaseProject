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

std::string StringColumn::getColumnType() const
{

}

std::string StringColumn::valueAt(const unsigned int& index) const
{

}

std::vector<unsigned int> StringColumn::getIndexesOfRowsWithValues(const std::string& value) const
{

}

void StringColumn::updateRowByIndex(const unsigned int& index, const std::string& value)
{

}

void StringColumn::deleteRowByIndex(const unsigned int& index)
{

}

void StringColumn::insertNewRowWith(const std::string& value)
{

}