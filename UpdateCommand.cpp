#include "UpdateCommand.h"
#include "Converter.h"
#include "CellInterface.h"
#include "Cell.h"

UpdateCommand::UpdateCommand(const std::string& name) : CommandInterface(name)
{

}

UpdateCommand::~UpdateCommand()
{

}

void UpdateCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while updating the specific table in the database!" << std::endl;
        std::cout << std::endl;
        return;
    }

    std::vector<std::string> parametersConverted;
    Converter::convertLineToParametersList(parameters, parametersConverted);

    if(parametersConverted.size() != 5)
    {
        std::cerr << "Invalid number of arguments for update command!" << std::endl;
        std::cout << std::endl;
        return;
    }

    CellInterface<int>* converted1 = Converter::toInt(parametersConverted[1]);
    CellInterface<int>* converted2 = Converter::toInt(parametersConverted[3]);


    if(converted1->second() == false || converted1->first() < 0 || converted2->second() == false || converted2->first() < 0)
    {
        std::cerr << "Invalid index!" << std::endl;
        std::cout << std::endl;
        return;
    }
    
    database->updateTable(parametersConverted[0], converted1->first(), parametersConverted[2], converted2->first(), parametersConverted[4]);

    delete converted1;
    delete converted2;

    std::cout << "Updating completed!" << std::endl;
    std::cout << std::endl;
}