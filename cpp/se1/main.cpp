/*
 This is a simple language interpreter
 
 Name: Ara Bedrossian
 Username: arabed
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
    - In this phase use will input the instructions line by line (or from file)
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
   - Would like to be able to read or write the instruction set to or from a 
     file with comments and remarks
   - Would like to add HELP instruction to print out useful information
   - Would like to add more variable types e.g. FLOAT, DOUBLE, BOOL
   - Would like to add more operators e.g. DEC, ASSIGN, ADD, SUB, MUL, DIV,...
   - System wide errors could have higher granularity
*/

#include "main.h"
#include "programbuffer.h"

/*
  Main function
  This is the entry point for this program.

*/
int main(int argc, char *argv[])
{
    cout << "---------------------------" << endl;
    cout << "Simple Language Interpreter" << endl;
    cout << "Version: " << VERSION << endl;
    cout << "Author: " << AUTHOR << endl;
    cout << "---------------------------" << endl;
    cout << endl;
    cout << "Help:" << endl;
    cout << "  Use the sli (simple language interpreter) in two modes." << endl;
    cout << endl;
    cout << "    1.For direct input simply type;" << endl;
    cout << "          sli" << endl;
    cout << endl;
    cout << "    2.For input NDPL content from a flat text file and" << endl;
    cout << "      execute them immidiately simply type;" << endl;
    cout << "          sli -f <NDPL filename>" << endl;
    cout <<  endl;

    //State 1
    char lineInput[MAX_LINE_SIZE];
    ProgramBuffer* prgBuffer = new ProgramBuffer();
    
    cout << "Program has been initilized." << endl;
    cout << "Please enter NDPL instructions for maximum of ";
    cout << MAX_LINES << " lines" << endl;
    cout << endl;
        
    //State 2    
    int err = ERR_NO;
    if(argc==1)//direct (interactive) input
    {
        while(!prgBuffer->IsReadyForExecution())
        {
            cout << "[" << prgBuffer->NextLineNumber() << "]: ";
            cin >> lineInput;
            err = prgBuffer->Insert(lineInput);
            if(err!=ERR_NO)
            {
                cout << "*ERROR#" << int(err) << "*";
                cout << ": Please re-enter the instruction." << endl;
            }
        }
    }
    else if(argc==3 && argv[2]!=NULL)//reading from file
    {
        ifstream ndplfile;
        ndplfile.open(argv[2], ifstream::in);
        
        while(ndplfile.good() && !prgBuffer->IsReadyForExecution())
        {
            string line;
            getline (ndplfile,line);
            err = prgBuffer->Insert((char*)line.c_str());
            if(err!=ERR_NO)
            {
                cout << "Line:" << prgBuffer->NextLineNumber()+1;
                cout << "**" << line << endl;
                cout << "*ERROR#" << int(err) << "*";
                cout << ": Wrong instruction or long ndpl file." << endl;
                return EXIT_FAILURE;
                break;
            }        
        }
        ndplfile.close();
    }
    else
    {
        cout << "*ERROR* in option selection. Please re-run the program." << endl;
        return EXIT_FAILURE;
    }
  
    //State 3
    cout << endl;
    cout << "Checking the While nesting..." << endl;
    if(!prgBuffer->CheckWhileLoops())
    {
        cout << "*ERROR* while loop nesting or structure. Correct the instruction list." << endl;
        return EXIT_FAILURE;
    }
    cout << "Done." << endl;
    
    //State 4
    cout << endl;
    cout << "Executing the Program. Please wait..." << endl;
    prgBuffer->Execute();
    cout << "Done." << endl;
        
    //State 5
    cout << endl;
    //print the variables values
    for(int i=0; i<MAX_VARIABLES; i++)
    {
        cout << char('A'+i) << ":" << prgBuffer->VarValue(char('A'+i)) << endl;
    }
    cout << endl;
    
    //Make sure we cleanup the memory
    delete prgBuffer;
    
    return EXIT_SUCCESS;
}
