#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "ColumnInterface.h"

class DoubleColumn : public ColumnInterface
{
    private:
    std::vector<std::pair<double, bool>> data;

    public:
    DoubleColumn(const std::string& name);

    virtual std::string getColumnType() const override;
    virtual std::string valueAt(const unsigned int& index) const override;

    virtual std::vector<unsigned int> getIndexesOfRowsWithValues(const std::string& value) const override;
    virtual void updateRowByIndex(const unsigned int& index, const std::string& newValue) override;
    virtual void deleteRowByIndex(const unsigned int& index) override;
    virtual void insertNewRowWith(const std::string& value) override;
};