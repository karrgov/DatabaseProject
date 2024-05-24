#include "Program.h"

int main()
{
    Program* program = Program::getProgram();
    program->execute();

    delete program;
    return 0;
}