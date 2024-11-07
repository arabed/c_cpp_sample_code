/*
  Defines the Variables Array with their name(key) and Value
  Variables class holds the variable name values and support some 
  basic operations on variables
*/

#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "main.h"

class Variables
{
      
  public:
    /*
      Constructor
    */
    Variables();
    /*
      Destructor
    */
    ~Variables();

    /*
      Set the initial value of variable "X" by default to 0
      @arg char aVarName The variable name 
      @arg int aValue The assigned value
      @return ERR_NO is succeed and ERR_GENERAL is failed
    */
    int Set(char aVarName, int aValue=0);

    /*
      Returns the current value by giving the variable name
      @arg char aVarName The variable name
      @return The variable value
    */
    int Get(char aVarName);

    /*
      Add the current argument value to variable value accessing 
      by variable name (could be negative or positive)
      @arg char aVarName The variable name 
      @arg int aValue The value to increase with
      @return the result and update the variable value
    */
    int Inc(char aVarName, int aValue);

    /*
      Compares two variables value ans returns true is it is equal
      in any other case it returns false
      @arg char aVarName1 First variable
      @arg char aVarName2 Second variable
      @return True is the values are equal and False if not
    */
    bool Equals(char aVarName1, char aVarName2);

    /*
      Returns true is a variable with the given name does exist
      @arg char aVarName the variable name
      @return True is variable exists or else returns False
    */
    bool Exists(char aVarName);
     
  private:
   /*
     Search and find the variable index by name in internal array
     @arg char aValName Variable name
     @return Variable index in internal array, returns -1 if not found
   */
   int IndexOfVar(char aVarName);
   
   /*
     the actual value for this variable.
   */
   int iValue[MAX_VARIABLES];
};

#endif //_VARIABLETYPE_H_
