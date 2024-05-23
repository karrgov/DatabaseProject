#include "HelpCommand.h"

HelpCommand::HelpCommand(const std::string& name) : CommandInterface(name)
{

}

HelpCommand::~HelpCommand()
{

}

void HelpCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    std::cout << "open <filename>" << std::endl;
    std::cout << "---Opens a file, provided by the user." << std::endl;

    std::cout << "close" << std::endl;
    std::cout << "---Closes the opened file." << std::endl;

    std::cout << "save" << std::endl;
    std::cout << "---Saves to the opened file." << std::endl;

    std::cout << "saveas <filename>" << std::endl;
    std::cout << "---Saves the already opened file to a specific one, provided by the user." << std::endl;

    std::cout << "help" << std::endl;
    std::cout << "---Displays all of the available commands." << std::endl;

    std::cout << "exit" << std::endl;
    std::cout << "---Exits the program." << std::endl;

    std::cout << "import <tablename> <filename>" << std::endl;
    std::cout << "---Imports a new table into the database by table name and file name." << std::endl;

    std::cout << "showtables" << std::endl;
    std::cout << "---Displays a list of all loaded tables." << std::endl;

    std::cout << "describe <tablename>" << std::endl;
    std::cout << "---Shows all the types of the columns of the provided table." << std::endl;

    std::cout << "print <tablename>" << std::endl;
    std::cout << "---Prints the provided table." << std::endl;

    std::cout << "export <tablename> <filename>" << std::endl;
    std::cout << "---Exports the provided table to a specific file." << std::endl;

    std::cout << "Select <columnIndex> <value> <tablename>" << std::endl;
    std::cout << "---Prints all rows, which match the provided value." << std::endl;

    std::cout << "addcolumn <tablename> <columnname> <columntype>" << std::endl;
    std::cout << "---Adds a new column to the provided table." << std::endl;

    std::cout << "update <tablename> <searchColumnIndex> <searchValue> <targetColumnIndex> <targetValue>" << std::endl;
    std::cout << "Updates the provided table." << std::endl;

    
}