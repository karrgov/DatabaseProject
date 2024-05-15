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

    virtual std::string getColumnType() const override;
    virtual std::string valueAt(const unsigned int& index) const override;

    virtual std::vector<unsigned int> getIndexesOfRowsWithValues(const std::string& value) const override;
    virtual void updateRowByIndex(const unsigned int& index, const std::string& value) override;
    virtual void deleteRowByIndex(const unsigned int& index) override;
    virtual void insertNewRowWith(const std::string& value) override;
};