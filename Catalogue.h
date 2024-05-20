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

    void importTableFromFile(const std::string& tableName, const std::string& filename);
    void exportTableToFile(const std::string& tablename, const std::string& filename);

    void saveCatalogueToDefaultFile(const std::string& name);
    void saveCatalogueToDifferentFile(const std::string& name);

    void showAllTables() const;

    void innerJoinTables(const std::string& firstTableName, const unsigned int& firstColumnIndex, const std::string& secondTableName, const unsigned int& secondColumnIndex);

};