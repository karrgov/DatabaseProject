#pragma once
#include <iostream>
#include <vector>
#include <string>

class ColumnInterface
{
    private:
    std::string name;

    public:

    ColumnInterface(const std::string& name);
    virtual ~ColumnInterface();

    std::string getName() const;

    virtual std::string getColumnType() const = 0;
    virtual std::string valueAt(const unsigned int& index) const = 0;

    virtual std::vector<unsigned int> getIndexesOfRowsWithValues(const std::string& value) const = 0;
    virtual void updateRowByIndex(const unsigned int& index, const std::string& newValue) = 0;
    virtual void deleteRowByIndex(const unsigned int& index) = 0;
    virtual void insertNewRowWith(const std::string& value) = 0;


};