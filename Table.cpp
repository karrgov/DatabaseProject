/**
 * @file Table.cpp
 * @author Krasimir
 * @brief This class represents a singular table in the database
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <fstream>
#include <cassert>
#include "Table.h"
#include "ColumnFactory.h"
#include "Converter.h"

/**
 * @brief Construct a new Table:: Table object
 * 
 * @param name 
 * @param filename 
 */
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
            this->columns[currentCol]->insertNewCellWith(value);
        }
    }
    input.close();
}

Table::Table(const std::string& name, const std::vector<ColumnInterface*>& resultTable, const unsigned int& rows) 
{
    this->name = name;
    this->columns = resultTable;

    if(!resultTable.empty()) 
    {
        this->countRows = rows;
    } 
    else 
    {
        this->countRows = 0;
    }

    std::cout << "Please enter the filename: ";
    std::cin >> this->filename;
    this->saveToFile(this->filename);
}

/**
 * @brief Destroy the Table:: Table object
 * 
 */
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

/**
 * @brief Returns the name of the table
 * 
 * @return std::string 
 */
std::string Table::getName() const
{
    return this->name;
}

/**
 * @brief Returns the filename of the table
 * 
 * @return std::string 
 */
std::string Table::getFilename() const
{
    return this->filename;
}

/**
 * @brief Returns the count of rows
 * 
 * @return unsigned int 
 */
unsigned int Table::getCountOfRows() const
{
    return this->countRows;
}

/**
 * @brief Returns the count of columns
 * 
 * @return unsigned int 
 */
unsigned int Table::getNumberOfColumns() const
{
    return this->columns.size();
}

/**
 * @brief Returns the specific column at the given index
 * 
 * @param index 
 * @return const ColumnInterface* 
 */
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

/**
 * @brief Prints the table
 * 
 */
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

/**
 * @brief Prints the types of each column in the table
 * 
 */
void Table::describe() const
{
    for(ColumnInterface* element : this->columns)
    {
        std::cout << element->getColumnType() << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief Saves the table to a specific file
 * 
 * @param filename 
 */
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

    output << this->columns.size() << " " << this->countRows << std::endl;

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

/**
 * @brief Performs select operation on the table
 * 
 * @param index 
 * @param value 
 */
void Table::select(const unsigned int& index, const std::string& value) const
{
    if(index >= this->columns.size())
    {
        std::cerr << "Invalid column index!" << std::endl;
        std::cout << std::endl;
        return;
    }
    std::vector<unsigned int> indexes = this->columns[index]->getIndexesOfCellsWithValues(value);

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

/**
 * @brief Adds a new column to the table
 * 
 * @param columnName 
 * @param columnType 
 */
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
        newColumn->insertNewCellWith("NULL");
    }
}

/**
 * @brief Updates the table
 * 
 * @param index 
 * @param searchValue 
 * @param targetIndex 
 * @param targetValue 
 */
void Table::update(const unsigned int& index, const std::string& searchValue, const unsigned int& targetIndex, const std::string& targetValue)
{
    if(index >= this->columns.size() || targetIndex >= this->columns.size())
    {
        std::cerr << "Invalid column index!" << std::endl;
        std::cout << std::endl;
        return;
    }

    std::vector<unsigned int> indexesToBeUpdated = this->columns[index]->getIndexesOfCellsWithValues(searchValue);

    for(unsigned int number : indexesToBeUpdated)
    {
        this->columns[targetIndex]->updateCellByIndex(number, targetValue);
    }
}

/**
 * @brief Deletes from the table
 * 
 * @param index 
 * @param searchValue 
 */
void Table::deleteFunc(const unsigned int& index, const std::string& searchValue)
{
    if(index >= this->columns.size())
    {
        std::cerr << "Invalid column index" << std::endl;
        std::cout << std::endl;
        return;
    }

    std::vector<unsigned int> indexes = this->columns[index]->getIndexesOfCellsWithValues(searchValue);

    unsigned int compennsationForDeletion = 0;

    for(unsigned int number : indexes)
    {
        number = number - compennsationForDeletion;

        for(ColumnInterface* element : this->columns)
        {
            element->deleteCellByIndex(number);
        }
        compennsationForDeletion++;
    }
    this->countRows = this->countRows - indexes.size();
}

/**
 * @brief Inserts into the table
 * 
 * @param values 
 */
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
        element->insertNewCellWith(values[index]);
        index++;
    }
}

/**
 * @brief Renames the table
 * 
 * @param name 
 */
void Table::rename(const std::string& name)
{
    this->name = name;
}

/**
 * @brief Counts the occurrences in a column of the table
 * 
 * @param index 
 * @param searchValue 
 * @return unsigned int 
 */
unsigned int Table::count(const unsigned int& index, const std::string& searchValue)
{
    if(index >= this->columns.size())
    {
        std::cerr << "Invalid column index!" << std::endl;
        std::cout << std::endl;
        return 0;
    }
    std::vector<unsigned int> indexes = this->columns[index]->getIndexesOfCellsWithValues(searchValue);
    return indexes.size();
}

/**
 * @brief Performs aggregate to the table
 * 
 * @param index 
 * @param searchValue 
 * @param targetIndex 
 * @param operationName 
 * @return double 
 */
double Table::aggregate(const unsigned int& index, const std::string& searchValue, const unsigned int& targetIndex, const std::string& operationName)
{
    if(index >= this->columns.size() || targetIndex >= this->columns.size())
    {
        std::cerr << "Invalid column index!" << std::endl;
        std::cout << std::endl;
        return 0;
    }

    std::string typeOfColumnTarget = this->columns[targetIndex]->getColumnType();

    if(typeOfColumnTarget != "int" && typeOfColumnTarget != "double")
    {
        std::cerr << "Target column is not int or double!" << std::endl;
        std::cout << std::endl;
        return 0;
    }

    std::vector<unsigned int> indexes = this->columns[index]->getIndexesOfCellsWithValues(searchValue);
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
            result = std::min(element, result);
        }
    }
    else
    {
        std::cerr << "Invalid operation!" << std::endl;
        std::cout << std::endl;
    }

    return result;
}
