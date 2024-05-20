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
            std::string value;
            std::getline(input, value);
            this->columns[currentCol]->insertNewRowWith(value);
        }
    }
    input.close();
}

Table::~Table()
{
    this->name.clear();
    this->filename.clear();

    for(ColumnInterface* element : this->columns)
    {
        delete element;
    }
    this->columns.clear();
}

std::string Table::getName() const
{
    return this->name;
}

std::string Table::getFilename() const
{
    return this->filename;
}

unsigned int Table::getCountOfRows() const
{
    return this->countRows;
}

const ColumnInterface* Table::columnAt(const unsigned int& index) const
{
    if(index >= this->columns.size())
    {
        std::cerr << "Invalid column index" << std::endl;
        return nullptr;
    }
    return this->columns[index];
}

void Table::print() const
{
    std::cout << "Content of table" << this->name << ":" << std::endl;
    for(ColumnInterface* element : this->columns)
    {
        std::cout << element->getName() << " ";
    }
    std::cout << std::endl;

    for(int i = 0; i < this->countRows; i++)
    {
        for(ColumnInterface* element : this->columns)
        {
            std::cout << element->valueAt(i) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Table::describe() const
{
    for(ColumnInterface* element : this->columns)
    {
        std::cout << element->getColumnType() << " ";
    }
    std::cout << std::endl;
}

void Table::saveToFile(const std::string& filename) const
{
    std::ofstream output(filename, std::ios::out | std::ios::trunc);

    if(!output)
    {
        std::cerr << "Invalid file!" << std::endl;
        output.close();
        return;
    }

    output << this->columns.size() << this->countRows << std::endl;

    for(ColumnInterface* element : this->columns)
    {
        output << element->getName() << " " << element->getColumnType() << std::endl;
        for(int i = 0; i < countRows; i++)
        {
            output << element->valueAt(i) << std::endl;
        }
    }
    output.close();
}

void Table::select(const unsigned int& index, const std::string& value) const
{
    if(index >= this->columns.size())
    {
        std::cerr << "Invalid column index!" << std::endl;
        return;
    }
    std::vector<unsigned int> indexes = this->columns[index]->getIndexesOfRowsWithValues(value);

    for(unsigned int number : indexes)
    {
        for(ColumnInterface* element : this->columns)
        {
            std::cout << element->valueAt(number) << " ";
        }
        std::cout << std::endl;
    }
}

void Table::addColumn(const std::string& columnName, const std::string& columnType)
{
    ColumnInterface* newColumn = ColumnFactory::createColumn(columnName, columnType);

    if(newColumn == nullptr)
    {
        std::cerr << "Invalid type for column" << std::endl;
        return;
    }

    this->columns.push_back(newColumn);
    for(int i = 0; i < this->countRows; i++)
    {
        newColumn->insertNewRowWith("NULL");
    }
}

void Table::update(const unsigned int& index, const std::string& searchValue, const unsigned int& targetIndex, const std::string& targetValue)
{
    if(index >= this->columns.size() || targetIndex >= this->columns.size())
    {
        std::cerr << "Invalid column index!" << std::endl;
        return;
    }

    std::vector<unsigned int> indexesToBeUpdated = this->columns[index]->getIndexesOfRowsWithValues(searchValue);

    for(unsigned int number : indexesToBeUpdated)
    {
        this->columns[targetIndex]->updateRowByIndex(number, targetValue);
    }
}

void Table::deleteFunc(const unsigned int& index, const std::string& searchValue)
{
    if(index >= this->columns.size())
    {
        std::cerr << "Invalid column index" << std::endl;
        return;
    }

    std::vector<unsigned int> indexes = this->columns[index]->getIndexesOfRowsWithValues(searchValue);

    unsigned int compennsationForDeletion = 0;

    for(unsigned int number : indexes)
    {
        number = number - compennsationForDeletion;

        for(ColumnInterface* element : this->columns)
        {
            element->deleteRowByIndex(number);
        }
        compennsationForDeletion++;
    }
    this->countRows = this->countRows - indexes.size();
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
