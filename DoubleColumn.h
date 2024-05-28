#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "CellInterface.h"
#include "ColumnInterface.h"

class DoubleColumn : public ColumnInterface
{
    private:
    std::vector<CellInterface<double>*> data;

    public:
    DoubleColumn(const std::string& name);
    ~DoubleColumn();

    DoubleColumn(const DoubleColumn& other) = delete;
    DoubleColumn& operator=(const DoubleColumn& other) = delete;

    virtual std::string getColumnType() const override;
    virtual std::string valueAt(const unsigned int& index) const override;

    virtual std::vector<unsigned int> getIndexesOfCellsWithValues(const std::string& value) const override;
    virtual void updateCellByIndex(const unsigned int& index, const std::string& value) override;
    virtual void deleteCellByIndex(const unsigned int& index) override;
    virtual void insertNewCellWith(const std::string& value) override;
};