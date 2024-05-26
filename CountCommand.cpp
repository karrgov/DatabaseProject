#include "CountCommand.h"
#include "Converter.h"
#include "CellInterface.h"
#include "Cell.h"

CountCommand::CountCommand(const std::string& name) : CommandInterface(name)
{

}

CountCommand::~CountCommand()
{

}

void CountCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while counting in the specific table in the database!" << std::endl;
        return;
    }

    std::vector<std::string> parametersConverted;
    Converter::convertLineToParametersList(parameters, parametersConverted);

    if(parametersConverted.size() != 3)
    {
        std::cerr << "Invalid number of arguments for count command!" << std::endl;
        return;
    }

    CellInterface<int>* converted1 = Converter::toInt(parametersConverted[1]);

    if(converted1->second() == false || converted1->first() < 0)
    {
        std::cerr << "Invalid index!" << std::endl;
        return;
    }

    unsigned int countResult = database->countInTable(parametersConverted[0], converted1->first(), parametersConverted[2]);
    std::cout << "Count is: " << countResult << std::endl;

    delete converted1;
}