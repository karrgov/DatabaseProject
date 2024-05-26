#include <iostream>
#include <fstream>
#include <cassert>
#include "Table.h"
#include "ColumnFactory.h"
#include "Converter.h"

Table::Table(const std::string& name, const std::string filename)
{
    // std::cout << "Constructor called!" << std::endl;
    this->name = name;
    this->filename = filename;

    std::ifstream input(filename, std::ios::in);

    if(!input)
    {
        std::cerr << "Invalid file!" << std::endl;
        std::cout << std::endl;
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
            std::cout << std::endl;
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

unsigned int Table::getNumberOfColumns() const
{
    return this->columns.size();
}

const ColumnInterface* Table::columnAt(const unsigned int& index) const
{
    if(index >= this->columns.size())
    {
        std::cerr << "Invalid column index" << std::endl;
        std::cout << std::endl;
        return nullptr;
    }
    return this->columns[index];
}

void Table::print() const
{
    std::cout << "Content of table " << this->name << ":" << std::endl;
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
        std::cout << std::endl;
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
        std::cout << std::endl;
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
    std::cout << std::endl;
}

void Table::addColumn(const std::string& columnName, const std::string& columnType)
{
    ColumnInterface* newColumn = ColumnFactory::createColumn(columnName, columnType);

    if(newColumn == nullptr)
    {
        std::cerr << "Invalid type for column" << std::endl;
        std::cout << std::endl;
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
        std::cout << std::endl;
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
        std::cout << std::endl;
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
    if(values.size() != this->columns.size())
    {
        std::cerr << "Inserted row does not match the number of elements!" << std::endl;
        std::cout << std::endl;
        return;
    }

    unsigned int index = 0;
    bool isTypeTheSame = true;

    for(ColumnInterface* element : this->columns)
    {
        std::string currentType = element->getColumnType();

        if(currentType == "string")
        {
            if(Converter::isString(values[index]) == false && Converter::isNull(values[index]) == false)
            {
                isTypeTheSame = false;
                break;
            }
        }
        else if(currentType == "int")
        {
            if(Converter::toInt(values[index])->second() == false && Converter::isNull(values[index]) == false)
            {
                isTypeTheSame = false;
                break;
            }
        }
        else if(currentType == "double")
        {
            if(Converter::toDouble(values[index])->second() == false && Converter::isNull(values[index]) == false)
            {
                isTypeTheSame = false;
                break;
            } 
        }
        else
        {
            isTypeTheSame = false;
            break;
        }
        index++;
    }

    if(isTypeTheSame == false)
    {
        std::cerr << "Invalid type!" << std::endl;
        std::cout << std::endl;
        return;
    }

    index = 0;
    this->countRows++;

    for(ColumnInterface* element : this->columns)
    {
        element->insertNewRowWith(values[index]);
        index++;
    }
}

void Table::rename(const std::string& name)
{
    this->name = name;
}

unsigned int Table::count(const unsigned int& index, const std::string& searchValue)
{
    if(index >= this->columns.size())
    {
        std::cerr << "Invalid column index!" << std::endl;
        std::cout << std::endl;
        return 0;
    }
    std::vector<unsigned int> indexes = this->columns[index]->getIndexesOfRowsWithValues(searchValue);
    return indexes.size();
}

double Table::aggregate(const unsigned int& index, const std::string& searchValue, const unsigned int& targetIndex, const std::string& operationName)
{
    if(index >= this->columns.size() || targetIndex >= this->columns.size())
    {
        std::cerr << "Invalid column index!" << std::endl;
        std::cout << std::endl;
        return 0;
    }

    std::string typeOfColumnTarget = this->columns[targetIndex]->getColumnType();

    if(typeOfColumnTarget != "int" || typeOfColumnTarget != "double")
    {
        std::cerr << "Target column is not int or double!" << std::endl;
        std::cout << std::endl;
        return 0;
    }

    std::vector<unsigned int> indexes = this->columns[index]->getIndexesOfRowsWithValues(searchValue);
    std::vector<double> temporary;

    for(unsigned int number : indexes)
    {
        double current = Converter::toDouble(this->columns[targetIndex]->valueAt(number))->first();
        temporary.push_back(current);
    }

    double result = 0;
    if(operationName == "sum")
    {
        result = 0;
        for(double element : temporary)
        {
            result = result + element;
        }
    }
    else if(operationName == "product")
    {
        result = 1;
        for(double element : temporary)
        {
            result = result * element;
        }
    }
    else if(operationName == "maximum")
    {
        for(double element : temporary)
        {
            result = std::max(element, result);
        }
    }
    else if(operationName == "minimum")
    {
        for(double element : temporary)
        {
            result = std::max(element, result);
        }
    }
    else
    {
        std::cerr << "Invalid operation!" << std::endl;
        std::cout << std::endl;
    }

    return result;
}
