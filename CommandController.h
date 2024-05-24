#include "CommandInterface.h"

class CommandController
{
    private:
    std::vector<CommandInterface*> allCommands;

    public:
    CommandController(const std::vector<CommandInterface*>& commands);
    ~CommandController();

    CommandController(const CommandController& other) = delete;
    CommandController& operator=(const CommandController& other) = delete;

    bool isCommandAvailable(Catalogue*& database);
};