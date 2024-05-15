#include <iostream>
#include <fstream>
#include <cassert>
#include "Table.h"
#include "ColumnFactory.h"
#include "Converter.h"

Table::Table(const std::string& name, const std::string filename)
{

}

Table::~Table()
{

}

std::string Table::getName() const
{

}

std::string Table::getFilename() const
{

}

unsigned int Table::getCountOfRows() const
{

}

const ColumnInterface* Table::columnAt(const unsigned int& index) const
{

}

void Table::print() const
{

}

void Table::describe() const
{

}

void Table::saveToFile(const std::string& filename) const
{

}

void Table::select(const unsigned int& index, const std::string& value) const
{

}

void Table::addColumn(const std::string& tableName, const std::string& tableType)
{

}

void Table::update(const unsigned int& index, const std::string& searchValue, const unsigned int& targetIndex, const std::string& targetValue)
{

}

void Table::deleteFunc(const unsigned int& index, const std::string& searchValue)
{

}

void Table::insert(const std::vector<std::string>& values)
{

}

void Table::rename(const std::string& name)
{

}

unsigned int count(const unsigned int& index, const std::string& searchValue)
{

}

double Table::aggregate(const unsigned int& index, const std::string& searchValue, const unsigned int& targetIndex, const std::string& operationName)
{
    
}
