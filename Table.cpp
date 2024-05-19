#include <iostream>
#include <fstream>
#include <cassert>
#include "Table.h"
#include "ColumnFactory.h"
#include "Converter.h"

Table::Table(const std::string& name, const std::string filename)
{
    this->name = name;
    this->filename = filename;

    std::ifstream input(filename, std::ios::in);

    if(!input)
    {
        std::cerr << "Invalid file!" << std::endl;
        input.close();
        return;
    }

    int columns;
    int rows;
    input >> columns >> rows;

    this->countRows = rows;
    this->columns.resize(columns, nullptr);

    for(int currentCol = 0; currentCol < columns; currentCol++)
    {
        std::string columnName;
        std::string columnType;

        input >> columnName >> columnType;
        input.ignore(1024, '\n');

        ColumnInterface* facCol = ColumnFactory::createColumn(columnName, columnType);

        if(!facCol)
        {
            std::cerr << "Invalid column type!" << std::endl;
            input.close();
            return;
        }

        this->columns[currentCol] = facCol;

        for(int currentRow = 0; currentRow < rows; currentRow++)
        {
            
        }


    }
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
