/*
 This is ProgramBuffer class implimentation
 This class holds the program instructions
*/

#include "programbuffer.h"

//Constructor
ProgramBuffer::ProgramBuffer()
{
    //Initilize the Program Counter
    iPC = 0;
    iIsReadyForExecute = false;
    iVars = new Variables();
}

//Destructor
ProgramBuffer::~ProgramBuffer()
{
    delete iVars;
}


/*
Returns the next available program buffer line number for instruction input
*/
int ProgramBuffer::NextLineNumber()
{
    return iPC;
}

/*
Accept a input line and return the next available program buffer line number
This function will return 
  ERR_GENERAL if instruction is unknown
  ERR_SYNTAX if there is something wrong with instruction syntax
  ERR_VARIABLE_NAMING if there is something wrong with variable naming
*/
int ProgramBuffer::Insert(char* aInstruction)
{
    int ret = ERR_NO;
    //remove the white spaces and change all the characters to uppercase
    aInstruction = strupr(aInstruction);
    
    //Check the instruction and its syntax
    if(strncmp(aInstruction,INST_COPY,strlen(INST_COPY))==0)
    {
        if(iVars->Set(aInstruction[5],iVars->Get(aInstruction[7]))==ERR_NO)
        {
            if(!IncPC())
            {
            //program buffer is full, lets execute
            iIsReadyForExecute = true;
            }
        }
        else
        {
            ret = ERR_VARIABLE_NAMING;
        }
    }
    else if(strncmp(aInstruction,INST_INC,strlen(INST_INC))==0)
    {
        if(iVars->Inc(aInstruction[4],1)==ERR_NO)
        {
            if(!IncPC())
            {
            //program buffer is full, lets execute
            iIsReadyForExecute = true;
            }
        }
        else
        {
            ret = ERR_VARIABLE_NAMING;
        }
    }
    else if(strncmp(aInstruction,INST_WHILEB,strlen(INST_WHILEB))==0)
    {
        if(!IncPC())
        {
        //program buffer is full, lets execute
        iIsReadyForExecute = true;
        }
    }
    else if(strncmp(aInstruction,INST_WHILEE,strlen(INST_WHILEE))==0)
    {
        if(!IncPC())
        {
        //program buffer is full, lets execute
        iIsReadyForExecute = true;
        }
    }
    else if(strncmp(aInstruction,INST_END,strlen(INST_END))==0)
    {
        iIsReadyForExecute = true;
    }
    else
    {
      ret = ERR_GENERAL;
    }
  
    return ret;
}

/*
Increate the Program Counter
@return false if it reaches it's maximum limit
*/
bool ProgramBuffer::IncPC()
{
     bool ret = true;
     iPC++;
     if(iPC>MAX_LINES)
     {
         ret=false;
     }
     return ret;
}
    
bool ProgramBuffer::IsReadyForExecution()
{
    return iIsReadyForExecute;
}

/*
Returns the value of a given variable
*/
int ProgramBuffer::VarValue(char aVarName)
{
    return iVars->Get(aVarName);
}

/*
Returns 0 if it executes successfully and returns
  -1 if not for any general error
  -3 if there is a WHILE LOOP definition problem
*/
int ProgramBuffer::Execute()
{
    return 0;
}
