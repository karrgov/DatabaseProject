/**
 * @file Main.cpp
 * @author Krasimir
 * @brief This class is the main of the program. That is where the whole project starts
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Program.h"

int main()
{
    Program* program = Program::getProgram();
    program->execute();

    delete program;
    return 0;
}