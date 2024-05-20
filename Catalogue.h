#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Table.h"

class Catalogue
{
    private:
    std::vector<Table*> tables;
    std::string filename;

    public:
    Catalogue();
    ~Catalogue();

    Catalogue(const Catalogue& other) = delete;
    Catalogue& operator=(const Catalogue& other) = delete;
};