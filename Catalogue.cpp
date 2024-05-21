#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Catalogue.h"
#include "Table.h"

Catalogue::Catalogue(const std::string& filename)
{
    std::ifstream inputFile(filename, std::ios::in);

    if(!inputFile)
    {
        std::cerr << "Invalid file!" << std::endl;
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

int Catalogue::findTableIndexByName(const std::vector<Table*>& tables, const std::string& searchName)
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
        return;
    }

    Table* newTable = new Table(tableName, filename);

    this->tables.push_back(newTable);
}

void Catalogue::exportTableToFile(const std::string& tablename, const std::string& filename)
{
    
}

void Catalogue::saveCatalogueToDefaultFile(const std::string& name)
{
    
}

void Catalogue::saveCatalogueToDifferentFile(const std::string& name)
{

}

void Catalogue::showAllTables() const
{

}

void Catalogue::innerJoinTables(const std::string& firstTableName, const unsigned int& firstColumnIndex, const std::string& secondTableName, const unsigned int& secondColumnIndex)
{
    
}