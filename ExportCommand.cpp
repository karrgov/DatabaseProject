#include "ExportCommand.h"
#include "Converter.h"

ExportCommand::ExportCommand(const std::string& name) : CommandInterface(name)
{

}

ExportCommand::~ExportCommand()
{

}

void ExportCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while exporting from the database!" << std::endl;
        return;
    }

    std::vector<std::string> parametersConverted;
    Converter::convertLineToParametersList(parameters, parametersConverted);

    if(parametersConverted.size() != 2)
    {
        std::cerr << "Invalid number of arguments for export command!" << std::endl;
        return;
    }

    database->exportTableToFile(parametersConverted[0], parametersConverted[1]);
}