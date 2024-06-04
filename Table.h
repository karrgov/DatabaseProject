#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "ColumnInterface.h"

class Table
{
    private:
    std::string name;
    std::string filename;
    unsigned int countRows;
    std::vector<ColumnInterface*> columns;

    public:
    Table(const std::string& name, const std::string filename);
    Table(const std::string& name, const std::vector<ColumnInterface*>& resultTable, const unsigned int& rows);
    ~Table();

    Table(const Table& other) = delete;
    Table& operator=(const Table& other) = delete;

    std::string getName() const;
    std::string getFilename() const;
    unsigned int getCountOfRows() const;
    unsigned int getNumberOfColumns() const;
    const ColumnInterface* columnAt(const unsigned int& index) const;
    void print() const;
    void describe() const;
    void saveToFile(const std::string& filename) const;
    void select(const unsigned int& index, const std::string& value) const;
    void addColumn(const std::string& columnName, const std::string& columnType);

    void update(const unsigned int& index, const std::string& searchValue, const unsigned int& targetIndex, const std::string& targetValue);

    void deleteFunc(const unsigned int& index, const std::string& searchValue);
    void insert(const std::vector<std::string>& values);
    void rename(const std::string& name);
    unsigned int count(const unsigned int& index, const std::string& searchValue);

    double aggregate(const unsigned int& index, const std::string& searchValue, const unsigned int& targetIndex, const std::string& operationName);

};