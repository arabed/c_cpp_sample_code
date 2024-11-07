/*
Implements the Variables Array with their name(key) and Value
Variable type class holds the variable name values and support some basic operations
*/

#include "main.h"
#include "variables.h"

//Constructor
VariableType::VariableType()
{
}

//Destructor
VariableType::~VariableType()
{
}

//Set the initial value to 0
int VariableType::Set(char aVarName, int aInitValue)
{
     int ret=ERR_NO;
     int index=IndexOfVar(aVarName);
     if(index>=0 && index<MAX_VARIABLE_ARRAY_SIZE)
     {
         iValue[index] = aInitValue;
     }
     else
     {
         ret=ERR_GENERAL;
     }

     return ret;
}
                        
//return the current value 
int VariableType::Get(char aVarName)
{
     int ret=ERR_NO;
     int index=IndexOfVar(aVarName);
     if(index>=0 && index<MAX_VARIABLE_ARRAY_SIZE)
     {
         ret=iValue[index];
     }
     else
     {
         ret=ERR_GENERAL;
     }

     return ret;
}

//add the current argument value to variables value 
//(could be negative or positive)
int VariableType::Inc(char aVarName, int aValue)
{
    return Set(aVarName,Get(aVarName)+aValue);
}

/*
Search and find the variable index by name in internal array
@arg char aValName Variable name which could be Upper or Lower case (e.g. 'A' or 'a')
@return Variable index in internal array, returns -1 if not found
*/
int VariableType::IndexOfVar(char aVarName)
{
    int index = FIRST_VARIABLE - aVarName;
    if(index<0 || index>=MAX_VARIABLE_ARRAY_SIZE)
    {
      index = ERR_GENERAL;
    }
    return index;
}
