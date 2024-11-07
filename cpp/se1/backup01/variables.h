/*
 Defines the Variables Array with their name(key) and Value
 Variable type class holds the variable name values and support some basic operations
*/

#ifndef _VARIABLES_H_
#define _VARIABLES_H_

class VariableType
{
      
  public:
    /*
    Constructor
    */
    VariableType();
    /*
    Destructor
    */
    ~VariableType();

    /*
    Set the initial value of variable "X" by default to 0
    @arg char aVarName The variable name 
    @arg int aValue The assigned value
    @return ERR_NO is succeed and ERR_GENERAL is failed
    */
    int Set(char aVarName, int aValue=0);
    /*
    Returns the current value by giving the variable name
    */
    int Get(char aVarName);
    /*
    add the current argument value to variable value accessing 
    by variable name (could be negative or positive)
    Returns the result and update the variable value
    */
    int Inc(char aVarName, int aValue);
     
  private:
   /*
   Search and find the variable index by name in internal array
   @arg char aValName Variable name which could be Upper or Lower case (e.g. 'A' or 'a')
   @return Variable index in internal array, returns -1 if not found
   */
   int IndexOfVar(char aVarName);
   
   /*
   the actual value for this variable.
   */
   int iValue[MAX_VARIABLE_ARRAY_SIZE];
};

#endif //_VARIABLETYPE_H_
