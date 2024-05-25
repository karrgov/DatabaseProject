#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Table.h"

class Catalogue
{
    private:
    std::vector<Table*> tables;
    std::string filename;

    public:
    Catalogue(const std::string& filename);
    ~Catalogue();

    Catalogue(const Catalogue& other) = delete;
    Catalogue& operator=(const Catalogue& other) = delete;

    int findTableIndexByName(const std::vector<Table*>& tables, const std::string& searchName) const;

    void importTableFromFile(const std::string& tableName, const std::string& filename);
    void exportTableToFile(const std::string& tableName, const std::string& filename);

    void saveCatalogueToDefaultFile();
    void saveCatalogueToDifferentFile(const std::string& filename);

    void showAllTables() const;

    void innerJoinTables(const std::string& firstTableName, const unsigned int& firstColumnIndex, const std::string& secondTableName, const unsigned int& secondColumnIndex);

    void describeTable(const std::string& name) const;
    void printTable(const std::string& name) const;
    void selectFromTable(const std::string& name, const unsigned int& index, const std::string& value) const;
    void addColumnToTable(const std::string& name, const std::string& columnName, const std::string& columnType);
    void updateTable(const std::string& name, const unsigned int& index, const std::string& searchValue, const unsigned int& targetIndex, const std::string& targetValue);
    void deleteFuncTable(const std::string& name, const unsigned int& index, const std::string& searchValue);

    

};