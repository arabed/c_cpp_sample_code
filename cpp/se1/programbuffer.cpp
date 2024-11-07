/*
  This is ProgramBuffer class implimentation
  This class holds the program instructions, checking and execution routines
*/
#include <cstring>
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
  @return The next available programming line from program buffer
*/
int ProgramBuffer::NextLineNumber()
{
    return iPC;
}

/*
  Accept a input line and return the next available program buffer line number
  @arg char* NDPL instruction. One instruction only
  @return This function will return 
          ERR_GENERAL if instruction is unknown
          ERR_SYNTAX if there is something wrong with instruction syntax
          ERR_VARIABLE_NAMING if there is something wrong with variable naming
*/
int ProgramBuffer::Insert(char* aInstruction)
{
    int ret = ERR_NO;
    //remove the white spaces and change all the characters to uppercase
    aInstruction = ConvToUpper(aInstruction);
    
    //Check the instruction and its syntax
    switch(Token(aInstruction))
    {
    case INST_COPY_TKN:
    case INST_INC_TKN:
    case INST_WHILENE_TKN:
    case INST_ENDWHILE_TKN:
        iPrgBuffer[iPC] = aInstruction;
        if(!IncPC())
        {
            ret =  ERR_GENERAL;
        }
        break;
    case INST_END_TKN:
        iPrgBuffer[iPC] = aInstruction; 
        iIsReadyForExecute = true;
        break;
    default:
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
     if(iPC>MAX_LINES-1)
     {
         ret=false;
     }
     return ret;
}

/*
  If program buffer is ready for execution, means the program has END 
  instruction in instructions list, then this function will return true.
  @return true if program has END statement and it is ready for execution if not it will return false
*/
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
   Utility function to convert a null terminated string to uppercase
   @arg aStr a null terminated character string
   @return the uppercase of the given string
*/
char* ProgramBuffer::ConvToUpper(char* aStr)
{
    int len = strlen(aStr);
    for(int i=0; i<len; i++)
    {
        if(aStr[i]>='a' && aStr[i]<='z')
        {
            aStr[i] -= ('a'-'A');//don't need calculation or magic numbers 
        }
    }
    return aStr;
}

/*
  Returns Instruction Token by parsing the string and checking the syntax and 
  making sure the allowed variables have been used. This program expected one
  instruction per line
  @arg aStr the NDPL instruction line
  @return instruction token INST_INC_TKN, INST_COPY_TKN...or it will 
          return ERR_XX in case of not able to parse
*/
int ProgramBuffer::Token(char* aInstruction)
{
    int ret = ERR_GENERAL;
    //Check the instruction and its syntax
    
    //Checks COPY instruction syntax
    if(strlen(aInstruction)==strlen(INST_COPY)+5 && 
        strncmp(aInstruction,INST_COPY,strlen(INST_COPY))==0)
    {
        if(
        (iVars->Exists(aInstruction[5]) && iVars->Exists(aInstruction[7]))
        &&
        //some fancy stuff need to be optimized later
        (aInstruction[4]=='(' && aInstruction[6]==',' && aInstruction[8]==')')
        )
        {
  	    ret = INST_COPY_TKN;
        }
        else
        {
            ret = ERR_VARIABLE_NAMING;
        }
    }
    //Checks INC instruction syntax
    else if(strlen(aInstruction)==strlen(INST_INC)+3 && 
        strncmp(aInstruction,INST_INC,strlen(INST_INC))==0)
    {
        if(
        iVars->Exists(aInstruction[4])
        &&
        //some fancy stuff need to be optimized later
        (aInstruction[3]=='(' && aInstruction[5]==')')
        )
        {
            ret = INST_INC_TKN;
        }
        else
        {
            ret = ERR_VARIABLE_NAMING;
        }
    }
    //Checks WHILENE instruction syntax
    else if(strncmp(aInstruction,INST_WHILENE,strlen(INST_WHILENE))==0)
    {
        if(
        (iVars->Exists(aInstruction[8]) && iVars->Exists(aInstruction[10]))
        &&
        //some fancy stuff need to be optimized later
        (aInstruction[7]=='(' && aInstruction[9]==',' && aInstruction[11]==')')
        )
        {
  	    ret = INST_WHILENE_TKN;
        }
        else
        {
            ret = ERR_VARIABLE_NAMING;
        }
    }
    else if(strncmp(aInstruction,INST_ENDWHILE,strlen(INST_ENDWHILE))==0)
    {
        ret = INST_ENDWHILE_TKN;
    }
    else if(strcmp(aInstruction,INST_END)==0)
    {
        ret = INST_END_TKN;
    }
    else
    {
      ret = ERR_GENERAL;
    }
  
    return ret;
}    

/*
  Recursive function to tag the whilene and endwhile instructions 
  information to each other.
  @argv int aWhileneLnNo Whilene instruction line number
  @return correcponding endwhile line number
*/
int ProgramBuffer::FindEndWhileLnNo(int aWhileneLnNo)
{
    int lineNum = -1;
    int intLineNum = -1;
    int token = -1;

    for(int i=aWhileneLnNo+1; i<MAX_LINES; i++)
    {
        //current instruction
        char* curInst = (char*)(iPrgBuffer[i]).c_str();
        token = Token(curInst);
                    
        if(token==INST_ENDWHILE_TKN)
        {
            //Tag the start and end of the while loop with line number
            //for execute function to use it
            char temp[5];
            
            sprintf(temp, ">%d", i);
            iPrgBuffer[aWhileneLnNo].append(temp);

            sprintf(temp, "<%d", aWhileneLnNo);
            iPrgBuffer[i].append(temp);

            lineNum = i;
            break;            
        }
        else if(token==INST_WHILENE_TKN)
        {
            intLineNum = FindEndWhileLnNo(i);
            if(intLineNum==-1)
            {
                break;
            }
            else
            {
                i = intLineNum;
            }
        }
        else if(token==INST_END_TKN)
        {
            break;
        }
    }

    return lineNum;
}
    
/*
 Checks and tags the while loop instructions
 @return True if it succeed else returns false
*/
bool ProgramBuffer::CheckWhileLoops()
{
    bool ret = true;
    bool stopExecution = false;
    int token = -1;
    
    //count while-end pair
    int whileBegin = 0;
    int whileEnd = 0;
    for(int i=0; i<MAX_LINES; i++)
    {
        //current instruction
        char* curInst = (char*)(iPrgBuffer[i]).c_str();
        token = Token(curInst);
        if(token==INST_WHILENE_TKN)
        {
            whileBegin++;
        }
        else if(token==INST_ENDWHILE_TKN)
        {
             whileEnd++;
        }
    }
    //compare the pairs
    if(whileBegin!=whileEnd)
    {
        ret = false;
        stopExecution = true;    
    }
                    
    int pc = 0;//program counter
    while(!stopExecution)
    {
        //current instruction to be executed
        char* curInst = (char*)(iPrgBuffer[pc]).c_str();
        token = Token(curInst);
        
        if(token==INST_WHILENE_TKN)
        {
            pc = FindEndWhileLnNo(pc);
            if(pc==-1)
            {
                ret = false;
                stopExecution = true;                
            }
        }
        else if(token==INST_END_TKN)
        {
            stopExecution = true;                
        }
        pc++;
    }

    return ret;
}

/*
  Executes the instruction and by using while tags amnage the while loops
  @return 0 if it executes successfully and returns
         ERR_GENERAL if not for any general error
*/
int ProgramBuffer::Execute()
{
    int ret = ERR_NO;
    bool stopExecution = false;
    int pc = 0;//program counter

    while(!stopExecution)
    {
        //current instruction to be executed
        char* curInst = (char*)(iPrgBuffer[pc]).c_str();

        //FOR DEBUGGING ONLY
        cout << "[" << pc << "]" << curInst << endl;

        switch(Token(curInst))
        {
        case INST_COPY_TKN:
    	    if(iVars->Set(curInst[5],iVars->Get(curInst[7]))==ERR_NO)
    	    {
    	        pc++;
    	    }
                else
    	    {
    	        ret = ERR_RUNTIME;
      	        stopExecution = true;
    	    }
            break;
        case INST_INC_TKN:
    	    if(iVars->Inc(curInst[4],1)==ERR_NO)
    	    {
    	        pc++;
    	    }
                else
    	    {
    	        ret = ERR_RUNTIME;
      	        stopExecution = true;
    	    }
            break;
        case INST_WHILENE_TKN:
            //if yes we need to break the loop i.e. got to endwhile+1
            if(iVars->Get(curInst[8])==iVars->Get(curInst[10]))
            {
   	            pc = atoi(curInst+13)+1;
            }
            else
            {
                pc++;
            }
            break;
        case INST_ENDWHILE_TKN:
   	        pc = atoi(curInst+9);
            break;
        case INST_END_TKN:
            stopExecution = true;
            break;
        default:
            stopExecution = true;
            ret = ERR_GENERAL;
        }        
    }
    return ret;
}
