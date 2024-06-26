/**
 * @file Catalogue.cpp
 * @author Krasimir
 * @brief This class represents a catalogue (list of tables)
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Catalogue.h"
#include "Table.h"
#include "ColumnFactory.h"

/**
 * @brief Construct a new Catalogue:: Catalogue object
 * 
 * @param filename 
 */
Catalogue::Catalogue(const std::string& filename)
{    // std::ifstream inputFile(filename, std::ios::in);

    // if(!inputFile)
    // {
    //     std::cerr << "Invalid file!" << std::endl;
    //     return;
    // }

    std::ifstream inputFile(filename, std::ios::in);

    if (!inputFile) 
    {
        std::cout << "The file you have provided does not exist and it will be created just now!" << std::endl;
        std::cout << std::endl;
        std::ofstream outputFile(filename);
        if (!outputFile) {
            std::cerr << "Failed to create file!" << std::endl;
            std::cout << std::endl;
            return;
        }

        unsigned int numOfTables;
        std::cout << "Enter the number of tables: ";
        std::cin >> numOfTables;

        outputFile << numOfTables << std::endl;

        for (unsigned int i = 0; i < numOfTables; i++) 
        {
            std::string tableName;
            std::string tableFilename;
            std::cout << "Enter table name for table " << i << ": ";
            std::cin >> tableName;
            std::cout << "Enter table filename for table " << i << ": ";
            std::cin >> tableFilename;

            outputFile << tableName << " " << tableFilename << std::endl;
        }

        outputFile.close();
        inputFile.open(filename);
    }

    if (!inputFile) {
        std::cerr << "Invalid file!" << std::endl;
        std::cout << std::endl;
        return;
    }

    unsigned int numOfTables;
    inputFile >> numOfTables;

    for(unsigned int i = 0; i < numOfTables; i++)
    {
        std::string tableName;
        std::string tableFilename;

        inputFile >> tableName >> tableFilename;

        this->tables.push_back(new Table(tableName, tableFilename));
    }

    this->filename = filename;
}

/**
 * @brief Destroy the Catalogue:: Catalogue object
 * 
 */
Catalogue::~Catalogue()
{
    for(Table* element : this->tables)
    {
        delete element;
    }
    this->tables.clear();
}

/**
 * @brief Finds a certain table's index in the catalogue through the table's name
 * 
 * @param tables 
 * @param searchName 
 * @return int 
 */
int Catalogue::findTableIndexByName(const std::vector<Table*>& tables, const std::string& searchName) const
{
    for(int i = 0; i < tables.size(); i++)
    {
        if(this->tables[i]->getName() == searchName)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Imports a table in the catalogue from a file
 * 
 * @param tableName 
 * @param filename 
 */
void Catalogue::importTableFromFile(const std::string& tableName, const std::string& filename)
{
    if(findTableIndexByName(this->tables, tableName) != -1)
    {
        std::cerr << "Table already exists!" << std::endl;
        std::cout << std::endl;
        return;
    }

    Table* newTable = new Table(tableName, filename);

    this->tables.push_back(newTable);
}

/**
 * @brief Exports a table from the catalogue to a specific file
 * 
 * @param tableName 
 * @param filename 
 */
void Catalogue::exportTableToFile(const std::string& tableName, const std::string& filename)
{
    if(findTableIndexByName(this->tables, tableName) == -1)
    {
        std::cerr << "Table does not exist!" << std::endl;
        std::cout << std::endl;
        return;
    }

    int indexOfTable = findTableIndexByName(this->tables, tableName);
    this->tables[indexOfTable]->saveToFile(filename);
}

/**
 * @brief Saves all changes made to the catalogue and its tables to the default file, used to construct it in the first place
 * 
 */
void Catalogue::saveCatalogueToDefaultFile()
{
    std::ofstream outputFile(this->filename, std::ios::out | std::ios::trunc);

    outputFile << this->tables.size() << std::endl;

    for(unsigned int i = 0; i < this->tables.size(); i++)
    {
        outputFile << this->tables[i]->getName() << " ";
        outputFile << this->tables[i]->getFilename() << std::endl;
    }

    outputFile.close();

    for(Table* element : this->tables)
    {
        element->saveToFile(element->getFilename());
    }
}

/**
 * @brief Saves all changes made to the catalogue and its tables to a specific file
 * 
 * @param filename 
 */
void Catalogue::saveCatalogueToDifferentFile(const std::string& newFilename)
{
    std::ofstream outputFile(newFilename, std::ios::out | std::ios::trunc);

    if(!outputFile)
    {
        std::cerr << "Invalid file!" << std::endl;
        std::cout << std::endl;
        return;
    }

    outputFile << this->tables.size() << std::endl;

    for(unsigned int i = 0; i < this->tables.size(); i++)
    {
        outputFile << this->tables[i]->getName() << " ";
        outputFile << this->tables[i]->getFilename() << std::endl;
    }

    outputFile.close();

    for(Table* element : this->tables)
    {
        element->saveToFile(element->getFilename());
    }
}

/**
 * @brief Prints the names of all tables in the catalogue
 * 
 */
void Catalogue::showAllTables() const
{
    for(Table* element : this->tables)
    {
        std::cout << element->getName() << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief Performs innerjoin to two tables in the catalogue
 * 
 * @param firstTableName 
 * @param firstColumnIndex 
 * @param secondTableName 
 * @param secondColumnIndex 
 */
void Catalogue::innerJoinTables(const std::string& firstTableName, const unsigned int& firstColumnIndex, const std::string& secondTableName, const unsigned int& secondColumnIndex)
{
    if(findTableIndexByName(this->tables, firstTableName) == -1 || findTableIndexByName(this->tables, secondTableName) == -1)
    {
        std::cerr << "Missing table/s! Can not perform innerjoin!" << std::endl;
        std::cout << std::endl;
        return;
    }

    int indexOfFirstTable = findTableIndexByName(this->tables, firstTableName);
    int indexOfSecondTable = findTableIndexByName(this->tables, secondTableName);

    const ColumnInterface* columnOfFirstTable = this->tables[indexOfFirstTable]->columnAt(firstColumnIndex);
    const ColumnInterface* columnOfSecondTable = this->tables[indexOfSecondTable]->columnAt(secondColumnIndex);


    if(columnOfFirstTable->getColumnType() != columnOfSecondTable->getColumnType())
    {
        std::cerr << "Column types do not match!" << std::endl;
        std::cout << std::endl;
        return;
    }

    if(firstColumnIndex >= this->tables[indexOfFirstTable]->getNumberOfColumns() || secondColumnIndex >= this->tables[indexOfSecondTable]->getNumberOfColumns())
    {
        std::cerr << "Invalid column index!" << std::endl;
        std::cout << std::endl;
        return;
    }

    std::vector<ColumnInterface*> resultTable;
    resultTable.push_back(ColumnFactory::createColumn("keyColumn", columnOfFirstTable->getColumnType()));

    for(unsigned int i = 0; i < this->tables[indexOfFirstTable]->getNumberOfColumns(); i++)
    {
        if(i == firstColumnIndex)
        {
            continue;
        }
        resultTable.push_back(ColumnFactory::createColumn(this->tables[indexOfFirstTable]->columnAt(i)->getName(), this->tables[indexOfFirstTable]->columnAt(i)->getColumnType()));
    }

    for(unsigned int i = 0; i < this->tables[indexOfSecondTable]->getNumberOfColumns(); i++)
    {
        if(i == secondColumnIndex)
        {
            continue;
        }
        resultTable.push_back(ColumnFactory::createColumn(this->tables[indexOfSecondTable]->columnAt(i)->getName(), this->tables[indexOfSecondTable]->columnAt(i)->getColumnType()));
    }

    bool doCellsMatch = false;
    unsigned int resultTableRows = 0;

    for(unsigned int i = 0; i < this->tables[indexOfFirstTable]->getCountOfRows(); i++)
    {
        std::vector<unsigned int> matchedCellsIndexes = columnOfSecondTable->getIndexesOfCellsWithValues(columnOfFirstTable->valueAt(i));

        if(matchedCellsIndexes.size() == 0) 
        {
            continue;
        }

        doCellsMatch = true;

        for(const unsigned int& element : matchedCellsIndexes) 
        {
            resultTableRows++;

            std::vector<std::string> valuesToBeAdded;
            valuesToBeAdded.push_back(columnOfFirstTable->valueAt(i));

            for(unsigned int j = 0; j < this->tables[indexOfFirstTable]->getNumberOfColumns(); ++j) 
            {
                if(j == firstColumnIndex) 
                {
                    continue;
                }

                valuesToBeAdded.push_back(this->tables[indexOfFirstTable]->columnAt(j)->valueAt(i));
            }

            for(unsigned int j = 0; j < this->tables[indexOfSecondTable]->getNumberOfColumns(); ++j) 
            {
                if(j == secondColumnIndex) {
                    continue;
                }

                valuesToBeAdded.push_back(this->tables[indexOfSecondTable]->columnAt(j)->valueAt(element));
            }

            for(unsigned int k = 0; k < resultTable.size(); ++k) 
            {
                resultTable[k]->insertNewCellWith(valuesToBeAdded[k]);
            }
        }  
    }

    if(doCellsMatch == false) 
    {
        std::cout << "There are no cells that match with one another! Innerjoin unsuccessful!" << std::endl;
        std::cout << std::endl;
    } 
    else 
    {
        std::cout << "Innerjoin successful!" << std::endl;
        std::cout << std::endl;
        
        for(unsigned int i = 0; i < resultTableRows; ++i) 
        {
            for(ColumnInterface* element : resultTable) 
            {
                std::cout << element->valueAt(i) << ' ';
            }

            std::cout << std::endl;
        }
    }

    std::cout << "Do you want to save the result table or not to save it? y/n?" << std::endl;
    std::string ans;
    std::cin >> ans;
    if(ans == "y")
    {
        Table* newTable = new Table("innerjoinTable", resultTable, resultTableRows);
        this->tables.push_back(newTable);
    }
    else
    {
        for(ColumnInterface* element : resultTable) 
        {
            delete element;
        }
        resultTable.clear();
    }

    // for(ColumnInterface* element : resultTable) 
    // {
    //     delete element;
    // }
    // resultTable.clear();
}

/**
 * @brief Prints the types of the columns in a specific table from the catalogue
 * 
 * @param name 
 */
void Catalogue::describeTable(const std::string& name) const
{
    if(findTableIndexByName(this->tables, name) == -1)
    {
        std::cerr << "Table does not exist!" << std::endl;
        std::cout << std::endl;
        return;
    }

    int index = findTableIndexByName(this->tables, name);
    this->tables[index]->describe();
}

/**
 * @brief Prints a specific table from the catalogue
 * 
 * @param name 
 */
void Catalogue::printTable(const std::string& name) const
{
    if(findTableIndexByName(this->tables, name) == -1)
    {
        std::cerr << "Table does not exist!" << std::endl;
        std::cout << std::endl;
        return;
    }

    int index = findTableIndexByName(this->tables, name);
    this->tables[index]->print();
}

/**
 * @brief Performs select on a specific table from the catalogue
 * 
 * @param name 
 * @param index 
 * @param value 
 */
void Catalogue::selectFromTable(const std::string& name, const unsigned int& index, const std::string& value) const
{
    if(findTableIndexByName(this->tables, name) == -1)
    {
        std::cerr << "Table does not exist!" << std::endl;
        std::cout << std::endl;
        return;
    }

    const unsigned int& indexFound = findTableIndexByName(this->tables, name);
    this->tables[indexFound]->select(index, value);
}

/**
 * @brief Adds a new column to a specific table in the catalogue
 * 
 * @param name 
 * @param columnName 
 * @param columnType 
 */
void Catalogue::addColumnToTable(const std::string& name, const std::string& columnName, const std::string& columnType)
{
    if(findTableIndexByName(this->tables, name) == -1)
    {
        std::cerr << "Table does not exist!" << std::endl;
        std::cout << std::endl;
        return;
    }

    const unsigned int& indexFound = findTableIndexByName(this->tables, name);
    this->tables[indexFound]->addColumn(columnName, columnType);
}

/**
 * @brief Updates a specific table in the catalogue
 * 
 * @param name 
 * @param index 
 * @param searchValue 
 * @param targetIndex 
 * @param targetValue 
 */
void Catalogue::updateTable(const std::string& name, const unsigned int& index, const std::string& searchValue, const unsigned int& targetIndex, const std::string& targetValue)
{
    if(findTableIndexByName(this->tables, name) == -1)
    {
        std::cerr << "Table does not exist!" << std::endl;
        std::cout << std::endl;
        return;
    }

    const unsigned int& indexFound = findTableIndexByName(this->tables, name);
    this->tables[indexFound]->update(index, searchValue, targetIndex, targetValue);
}

/**
 * @brief Deletes from a specific table in the catalogue
 * 
 * @param name 
 * @param index 
 * @param searchValue 
 */
void Catalogue::deleteFuncTable(const std::string& name, const unsigned int& index, const std::string& searchValue)
{
    if(findTableIndexByName(this->tables, name) == -1)
    {
        std::cerr << "Table does not exist!" << std::endl;
        std::cout << std::endl;
        return;
    }

    const unsigned int& indexFound = findTableIndexByName(this->tables, name);
    this->tables[indexFound]->deleteFunc(index, searchValue);
}

/**
 * @brief Inserts in a specific table in the catalogue
 * 
 * @param name 
 * @param values 
 */
void Catalogue::insertInTable(const std::string& name, const std::vector<std::string>& values)
{
    if(findTableIndexByName(this->tables, name) == -1)
    {
        std::cerr << "Table does not exist!" << std::endl;
        std::cout << std::endl;
        return;
    }

    const unsigned int& indexFound = findTableIndexByName(this->tables, name);
    this->tables[indexFound]->insert(values);
}

/**
 * @brief Renames a specific table in the catalogue
 * 
 * @param tablename 
 * @param name 
 */
void Catalogue::renameTable(const std::string& tablename, const std::string& name)
{
    if(findTableIndexByName(this->tables, tablename) == -1)
    {
        std::cerr << "Table does not exist!" << std::endl;
        std::cout << std::endl;
        return;
    }

    const unsigned int& indexFound = findTableIndexByName(this->tables, tablename);
    this->tables[indexFound]->rename(name);
}

/**
 * @brief Counts the occurrences in a column of a specific table in the catalogue
 * 
 * @param tablename 
 * @param index 
 * @param searchValue 
 * @return unsigned int 
 */
unsigned int Catalogue::countInTable(const std::string& tablename, const unsigned int& index, const std::string& searchValue)
{
    if(findTableIndexByName(this->tables, tablename) == -1)
    {
        std::cerr << "Table does not exist!" << std::endl;
        std::cout << std::endl;
        return 0;
    }

    const unsigned int& indexFound = findTableIndexByName(this->tables, tablename);
    return this->tables[indexFound]->count(index, searchValue);
}

/**
 * @brief Performs aggregate to a specific table in the catalogue
 * 
 * @param tablename 
 * @param index 
 * @param searchValue 
 * @param targetIndex 
 * @param operationName 
 * @return double 
 */
double Catalogue::aggregate(const std::string& tablename, const unsigned int& index, const std::string& searchValue, const unsigned int& targetIndex, const std::string& operationName)
{
    if(findTableIndexByName(this->tables, tablename) == -1)
    {
        std::cerr << "Table does not exist!" << std::endl;
        std::cout << std::endl;
        return 0;
    }

    const unsigned int& indexFound = findTableIndexByName(this->tables, tablename);
    return this->tables[indexFound]->aggregate(index, searchValue, targetIndex, operationName);
}