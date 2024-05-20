#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Catalogue.h"

Catalogue::Catalogue(const std::string& filename)
{

}

Catalogue::~Catalogue()
{
    
}

void importTableFromFile(const std::string& tableName, const std::string& filename);
void exportTableToFile(const std::string& tablename, const std::string& filename);

void saveCatalogueToDefaultFile(const std::string& name);
void saveCatalogueToDifferentFile(const std::string& name);

void showAllTables() const;

void innerJoinTables(const std::string& firstTableName, const unsigned int& firstColumnIndex, const std::string& secondTableName, const unsigned int& secondColumnIndex);