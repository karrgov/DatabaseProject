#include <iostream>
#include <vector>
#include <string>
#include "DoubleColumn.h"
#include "Converter.h"
#include "Cell.h"
#include "CellInterface.h"
#include <cmath>

const double DIFF = 0.00000001;

DoubleColumn::DoubleColumn(const std::string& name) : ColumnInterface(name)
{

}

DoubleColumn::~DoubleColumn()
{
    for(auto i : this->data)
    {
        delete i;
    }
    this->data.clear();
}

std::string DoubleColumn::getColumnType() const
{
    return "double";
}

std::string DoubleColumn::valueAt(const unsigned int& index) const
{
    if(index >= this->data.size())
    {
        std::cerr << "Invalid cell index!" << std::endl;
        return "";
    }

    if(data[index]->second() == false)
    {
        return "NULL";
    }
    return std::to_string(data[index]->first());
}

std::vector<unsigned int> DoubleColumn::getIndexesOfRowsWithValues(const std::string& value) const
{
    std::vector<unsigned int> result;

    CellInterface<double>* converted = Converter::toDouble(value);

    if(converted->second() == false)
    {
        if(Converter::isNull(value) == true)
        {
            int index = 0;

            for(auto i : this->data)
            {
                if(i->second() == false)
                {
                    result.push_back(index);
                }
                index++;
            }
        }
        delete converted;
        return result;
    }

    int index = 0;
    for(auto i : this->data)
    {
        if(i->second() == true && fabs(i->first() - converted->first()) < DIFF)
        {
            result.push_back(index);
        }
        index++;
    }
    delete converted;
    return result;
}

void DoubleColumn::updateRowByIndex(const unsigned int& index, const std::string& value)
{
    if(index >= this->data.size())
    {
        std::cerr << "Invalid cell index!" << std::endl;
        return;
    }

    CellInterface<double>* converted = Converter::toDouble(value);
    this->data[index] = converted;
    delete converted;
}

void DoubleColumn::deleteRowByIndex(const unsigned int& index)
{
    if(index >= this->data.size())
    {
        std::cerr << "Invalid cell index!" << std::endl;
        return;
    }
    
    for(int i = index + 1; i < this->data.size(); ++i)
    {
        this->data[i - 1] = this->data[i];
    }
    this->data.pop_back();
}
 
void DoubleColumn::insertNewRowWith(const std::string& value)
{
    CellInterface<double>* converted = Converter::toDouble(value);
    this->data.push_back(converted);
    delete converted;
}