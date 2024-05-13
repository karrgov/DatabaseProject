#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Cell.h"
#include "ColumnInterface.h"

class IntColumn : public ColumnInterface
{
    private:
    std::vector<std::pair<int, bool>> data;

    public:
    IntColumn(const std::string& name);

    virtual std::string getColumnType() const override;
    virtual std::string valueAt(const unsigned int& index) const override;

    virtual std::vector<unsigned int> getIndexesOfRowsWithValues(const std::string& value) const override;
    virtual void updateRowByIndex(const unsigned int& index, const std::string& newValue) override;
    virtual void deleteRowByIndex(const unsigned int& index) override;
    virtual void insertNewRowWith(const std::string& value) override;

};