/*
 This is a simple language interpreter
 
 Name: Ara Bedrossian
 Student #: 68157056
 Assignment: [os1] Observer(s) 
 
 Introduction:
   This file includes the entry point (i.e. main func).
   Main function/this program includes following states.
  <START>
  State 1: Initilization
    - The variables will be setup to initial value of zero
    - Correcponding objects will be instantiated
    - User will be prompt to input the instructions
  State 2: Input
    - In this phase use will input the instructions line by line
    - Upon each entry program will show the next line count.
    - The maximum number of line could be input for this program 
    is 100
    - Upon each line input, program will check the SYNTAX and VARIABLES.
    If these information are not correct, program will reject the line. 
    Program will offer that line for new input.
    - Upon inputing the "END" instruction program will move to 
    next state
  State 3: Pre-Execution Check
    - Program will check for WHILE loop errors and if it found
    any it will prompt user with corresponding iformation and it
    will terminate the program.
  State 4: Execution
    - Program will go over the instructions and execute them.
  State 5: Reporting
    - Program will print out the variables values
  <END>
  
 Wish List:
   (These are the useful features not included in the assignment requirements)
   - Would like to be able to read or write the instruction set to or from a file
   - Would like to add HELP instruction to print out useful information
   - Would like to add more variable types e.g. FLOAT, DOUBLE, BOOL
   - Would like to add more operators e.g. DEC, ASSIGN, ADD, SUB, MUL, DIV,...
*/

#include "main.h"
#include "programbuffer.h"

/*
  Main function
  This is the entry point for this program.

*/
int main(int argc, char *argv[])
{
    ProgramBuffer* prgBuffer = new ProgramBuffer();
    
    char str[LB_SIZE];
    cout << "Hello";
    cin >> str;
    cout << str;
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
