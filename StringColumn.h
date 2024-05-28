#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "CellInterface.h"
#include "ColumnInterface.h"

class StringColumn : public ColumnInterface
{
    private:
    std::vector<CellInterface<std::string>*> data;

    public:
    StringColumn(const std::string& name);
    ~StringColumn();

    StringColumn(const StringColumn& other) = delete;
    StringColumn& operator=(const StringColumn& other) = delete;

    virtual std::string getColumnType() const override;
    virtual std::string valueAt(const unsigned int& index) const override;

    virtual std::vector<unsigned int> getIndexesOfCellsWithValues(const std::string& value) const override;
    virtual void updateCellByIndex(const unsigned int& index, const std::string& value) override;
    virtual void deleteCellByIndex(const unsigned int& index) override;
    virtual void insertNewCellWith(const std::string& value) override;
};