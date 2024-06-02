/**
 * @file Program.cpp
 * @author Krasimir
 * @brief This class represents the whole Program, following the singleton design pattern because the program is a singular entity therefore making it impossible for two or more programs to exist at the same time
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Program.h"
#include "OpenCommand.h"
#include "CloseCommand.h"
#include "SaveCommand.h"
#include "SaveAsCommand.h"
#include "HelpCommand.h"
#include "ImportCommand.h"
#include "ShowtablesCommand.h"
#include "DescribeCommand.h"
#include "PrintCommand.h"
#include "ExportCommand.h"
#include "SelectCommand.h"
#include "AddcolumnCommand.h"
#include "UpdateCommand.h"
#include "DeleteCommand.h"
#include "InsertCommand.h"
#include "InnerjoinCommand.h"
#include "RenameCommand.h"
#include "CountCommand.h"
#include "AggregateCommand.h"

Program* Program::singletonProgram = nullptr;

/**
 * @brief Construct a new Program:: Program object
 * 
 */
Program::Program() : database(nullptr) 
{
    this->controller = new CommandController({
        new OpenCommand("open"),
        new CloseCommand("close"),
        new SaveCommand("save"),
        new SaveAsCommand("saveas"),
        new HelpCommand("help"),
        new ImportCommand("import"),
        new ShowtablesCommand("showtables"),
        new DescribeCommand("describe"),
        new PrintCommand("print"),
        new ExportCommand("export"),
        new SelectCommand("select"),
        new AddcolumnCommand("addcolumn"),
        new UpdateCommand("update"),
        new DeleteCommand("delete"),
        new InsertCommand("insert"),
        new InnerjoinCommand("innerjoin"),
        new RenameCommand("rename"),
        new CountCommand("count"),
        new AggregateCommand("aggregate")
    });
}

/**
 * @brief Returns the program
 * 
 * @return Program* 
 */
Program* Program::getProgram()
{
    if(singletonProgram == nullptr)
    {
        singletonProgram = new Program();
    }

    return singletonProgram;
}

/**
 * @brief Destroy the Program:: Program object
 * 
 */
Program::~Program()
{
    delete this->controller;
    this->controller = nullptr;

    delete this->database;
    this->database = nullptr;
}

/**
 * @brief Executes the program through the isCommandAvailable method
 * 
 */
void Program::execute()
{
    while(this->controller->isCommandAvailable(this->database))
    {

    }
}






