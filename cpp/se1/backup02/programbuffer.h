/*
 This is ProgramBuffer class definition
 This class holds the program instructions
*/

#ifndef _PROGRAMBUFFER_H_
#define _PROGRAMBUFFER_H_

#include "variables.h"

class ProgramBuffer
{
     
  public:
    /*
    Constructor
    */
    ProgramBuffer();
         
    /*
    Destructor
    */
    ~ProgramBuffer();

    /*
    Returns the next available program buffer line number for instruction input
    */
    int NextLineNumber();
    /*
    Accept a input line and return the next available program buffer line number
    This function will return 
      -1 if there is a SYNTAX ERROR (i.e. the instruction name of format is unknown)
      -2 if there is a wrong VARIABLE DEFINITION
    */
    int Insert(char* aInstruction);
    /*
    Returns the value of a given variable
    */
    int VarValue(char aVarName);
    /*
    If program buffer is ready for execution, means the program has END 
    instruction then this function will return true.
    @return true if program has END statement and it is ready for execution if not it will return false
    */
    bool IsReadyForExecution();
    /*
    Returns 0 if it executes successfully and returns
      -1 if not for any general error
      -3 if there is a WHILE LOOP definition problem
    */
    int Execute();
    
  private:
    /*
    Increate the Program Counter
    @return false if it reaches it's maximum limit
    */
    bool IncPC();
    
    int iPC; //internal program counter
    bool iIsReadyForExecute;//Indicates is program buffer has the END instruction
    
    char** iPrgBuffer[MAX_LINES];//The instructions buffer
    Variables* iVars;//The user programming variables
};

#endif //_PROGRAMBUFFER_H_
