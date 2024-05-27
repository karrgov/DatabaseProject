#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Catalogue.h"
#include "Table.h"
#include "ColumnFactory.h"

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

Catalogue::~Catalogue()
{
    for(Table* element : this->tables)
    {
        delete element;
    }
    this->tables.clear();
}

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

void Catalogue::saveCatalogueToDifferentFile(const std::string& filename)
{
    std::ofstream outputFile(this->filename, std::ios::out | std::ios::trunc);

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

void Catalogue::showAllTables() const
{
    for(Table* element : this->tables)
    {
        std::cout << element->getName() << " ";
    }
    std::cout << std::endl;
}

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
    resultTable.push_back(ColumnFactory::createColumn("key", columnOfFirstTable->getColumnType()));

    for(unsigned int i = 0; i < this->tables[indexOfFirstTable]->getNumberOfColumns(); i++)
    {
        if(i == firstColumnIndex)
        {
            continue;
        }
        resultTable.push_back(ColumnFactory::createColumn(this->tables[indexOfFirstTable]->columnAt(i)->getName(), this->tables[indexOfFirstTable]->columnAt(i)->getColumnType()));
    }

    

    

    
}

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