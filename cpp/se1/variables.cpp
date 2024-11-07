/*
  Implements the Variables Array with their name(key) and Value
  Variables class holds the variable name values and support some 
  basic operations on variables
*/

#include "main.h"
#include "variables.h"

//Constructor
Variables::Variables()
{
    for(int i=0; i<MAX_VARIABLES; i++)
    {
        iValue[i] = 0;
    }
}

//Destructor
Variables::~Variables()
{
}

/*
  Set the initial value of variable "X" by default to 0
  @arg char aVarName The variable name 
  @arg int aValue The assigned value
  @return ERR_NO is succeed and ERR_GENERAL is failed
*/
int Variables::Set(char aVarName, int aInitValue)
{
     int ret=ERR_NO;
     int index=IndexOfVar(aVarName);

     if(index>=0 && index<MAX_VARIABLES)
     {
         iValue[index] = aInitValue;
     }
     else
     {
         ret=ERR_GENERAL;
     }

     return ret;
}
                        
/*
  Returns the current value by giving the variable name
  @arg char aVarName The variable name
  @return The variable value
*/
int Variables::Get(char aVarName)
{
     int ret=ERR_NO;
     int index=IndexOfVar(aVarName);

     if(index>=0 && index<MAX_VARIABLES)
     {
         ret=iValue[index];
     }
     else
     {
         ret=ERR_GENERAL;
     }

     return ret;
}

/*
  Add the current argument value to variable value accessing 
  by variable name (could be negative or positive)
  @arg char aVarName The variable name 
  @arg int aValue The value to increase with
  @return the result and update the variable value
*/
int Variables::Inc(char aVarName, int aValue)
{
    return Set(aVarName,Get(aVarName)+aValue);
}

/*
  Compares two variables value ans returns true is it is equal
  in any other case it returns false
  @arg char aVarName1 First variable
  @arg char aVarName2 Second variable
  @return True is the values are equal and False if not
*/
bool Variables::Equals(char aVarName1, char aVarName2)
{
     bool ret = false;

     if(Exists(aVarName1) && Exists(aVarName2))
     {
         if(Get(aVarName1)==Get(aVarName2))
         {
             ret = true;
         }
     }

     return ret;
}
 
/*
  Returns true is a variable with the given name does exist
  @arg char aVarName the variable name
  @return True is variable exists or else returns False
*/
bool Variables::Exists(char aVarName)
{
    bool ret = false;

    if(IndexOfVar(aVarName)>=0)
    {
        ret = true;
    }

    return ret;
} 

/*
  Search and find the variable index by name in internal array
  @arg char aValName Variable name which could be Upper or Lower case (e.g. 'A' or 'a')
  @return Variable index in internal array, returns -1 if not found
*/
int Variables::IndexOfVar(char aVarName)
{
    int index = aVarName - FIRST_VARIABLE;

    if(index<0 || index>=MAX_VARIABLES)
    {
      index = ERR_GENERAL;
    }

    return index;
}
