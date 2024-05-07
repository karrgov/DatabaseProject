#include <iostream>
#include <vector>
#include <string>
#include "IntColumn.h"

IntColumn::IntColumn(const std::string& name) : ColumnInterface(name)
{

}

std::string IntColumn::getColumnType() const
{

}
std::string IntColumn::valueAt(const unsigned int& index) const
{

}

std::vector<unsigned int> IntColumn::getIndexesOfRowsWithValues(const std::string& value) const
{

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