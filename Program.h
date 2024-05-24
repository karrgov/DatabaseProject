#pragma once
#include "CommandController.h"
#include "Catalogue.h"

class Program
{
    private:
    static Program* singletonProgram;
    CommandController* controller;
    Catalogue* database;

    Program();

    public:
    static Program* getProgram();
    ~Program();

    Program(const Program& other) = delete;
    Program& operator=(const Program& other) = delete;

    void execute();
};