#include "InnerjoinCommand.h"
#include "Converter.h"
#include "CellInterface.h"
#include "Cell.h"

InnerjoinCommand::InnerjoinCommand(const std::string& name) : CommandInterface(name)
{

}

InnerjoinCommand::~InnerjoinCommand()
{

}

void InnerjoinCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while innerjoining the specific tables in the database!" << std::endl;
        return;
    }

    std::vector<std::string> parametersConverted;
    Converter::convertLineToParametersList(parameters, parametersConverted);

    if(parametersConverted.size() != 4)
    {
        std::cerr << "Invalid number of arguments for innerjoin command!" << std::endl;
        return;
    }

    CellInterface<int>* converted1 = Converter::toInt(parametersConverted[1]);
    CellInterface<int>* converted2 = Converter::toInt(parametersConverted[3]);


    if(converted1->second() == false || converted1->first() < 0 || converted2->second() == false || converted2->first() < 0)
    {
        std::cerr << "Invalid index!" << std::endl;
        return;
    }
    
    database->innerJoinTables(parametersConverted[0], converted1->first(), parametersConverted[2], converted2->first());

    delete converted1;
    delete converted2;
}