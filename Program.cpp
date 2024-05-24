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

Program* Program::singletonProgram = nullptr;

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
        new SelectCommand("select")
    });
}

Program* Program::getProgram()
{
    if(singletonProgram == nullptr)
    {
        singletonProgram = new Program();
    }

    return singletonProgram;
}

Program::~Program()
{
    delete this->controller;
    this->controller = nullptr;

    delete this->database;
    this->database = nullptr;
}

void Program::execute()
{
    while(this->controller->isCommandAvailable(this->database))
    {
        
    }
}






