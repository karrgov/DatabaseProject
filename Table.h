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
    ~Table();

    

};