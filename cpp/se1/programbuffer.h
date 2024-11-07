/*
  This is ProgramBuffer class definition
  This class holds the program instructions, checking and execution routines
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
      @return The next available programming line from program buffer
    */
    int NextLineNumber();
    
    /*
      Accept a input line and return the next available program buffer line number
      @arg char* NDPL instruction. One instruction only
      @return This function will return 
              ERR_GENERAL if instruction is unknown
              ERR_SYNTAX if there is something wrong with instruction syntax
              ERR_VARIABLE_NAMING if there is something wrong with variable naming
    */
    int Insert(char* aInstruction);
    
    /*
      Returns integer the value of a given variable
      @return integer value of a given variable
    */
    int VarValue(char aVarName);
    
    /*
      If program buffer is ready for execution, means the program has END 
      instruction in instructions list, then this function will return true.
      @return true if program has END statement and it is ready for execution if not it will return false
    */
    bool IsReadyForExecution();
    
    /*
      Executes the instruction and by using while tags amnage the while loops
      @return 0 if it executes successfully and returns
             ERR_GENERAL if not for any general error
    */
    int Execute();
    
    /*
     Checks and tags the while loop instructions
     @return True if it succeed else returns false
    */
    bool CheckWhileLoops();
    
    /*
       Utility function to convert a null terminated string to uppercase
       @arg aStr a null terminated character string
       @return the uppercase of the given string
    */
    char* ConvToUpper(char* aStr);
    
    /*
      Recursive function to tag the whilene and endwhile instructions 
      information to each other.
      @argv int aWhileneLnNo Whilene instruction line number
      @return correcponding endwhile line number
    */
    int FindEndWhileLnNo(int aWhileneLnNo);
  private:
    /*
      Increate the Program Counter
      @return false if it reaches it's maximum limit
    */
    bool IncPC();

    /*
      Returns Instruction Token by parsing the string and checking the syntax and 
      making sure the allowed variables have been used. This program expected one
      instruction per line
      @arg aInstruction the NDPL instruction line
      @return instruction token INST_INC_TKN, INST_COPY_TKN...or it will return ERR_XX in case of not able to parse
    */
    int Token(char* aInstruction);
    
    int iPC; //internal program counter
    bool iIsReadyForExecute;//Indicates is program buffer has the END instruction
    
    string iPrgBuffer[MAX_LINES];//The instructions line buffer
    Variables* iVars;//The user programming variables
   
};

#endif //_PROGRAMBUFFER_H_
