
Name:		Ara Bedrossian
Username:	arabed
Student #:	68157056
------------------------


Assignment:	[se1] sil (Simple Language Interpreter) 
----------


Description:	
-----------
This is a simple language interpreter
 
 Introduction:
   This program will accept NDPL instruction; will check them, execute and 
   display the results. NDPL instructions are consist of 5 i.e. COPY, INC, 
   WHILENE, ENDWHILE and END.
   This program will move through various stages and phases to complete its
   mandate. Overall this program have 5 states (stages) of execution.
   These states are as following;

  <START>
  State 1: Initilization
    - The variables will be setup to initial value of zero
    - Correcponding objects will be instantiated
    - User will be prompt to input the instructions (direct mode)
  State 2: Input
    - In this phase use will input the instructions line by line (direct mode)
      or
    - Program will read NDPL instructions from flat text file passed as one of 
      its arguments
    - Upon each entry program will show the next line count.
    - The maximum number of line could be input for this program 
    is 100
    - Upon each line input, program will check the SYNTAX and VARIABLES.
    If these information are not correct, program will reject the line. 
    - Program will offer that line for new input.(direct mode only)
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
 
 Delivarables:
  The program consists of the following files:
  - SOURCE:
    main.h		The constants and system wide required information.
    main.cc		Program entry module. Manages the program State Machine.
    programbuffer.h	Defines class to hold, handle and execute NDPL instructions
    programbuffer.cc	Implements class to hold, handle and execute NDPL instructions
    variables.h		Defines class to handle the variables required by NDPL	
    variables.cc	Implements class to handle the variables required by NDPL	

  - DATA:
    ndpl.txt		A NDPL instruction list sample document

  - DOC:
    Readme.txt		Provides general information about this program (this file)

  - MAKEFILES:
    Makefile.win	To build the binary target in Windows environment (Dev-C++ required)
    Makefile.linux	To build the binary target in Linux environment

  - EXECUTABLE:
    sli.exe		Executable for Windows
    sli			Executable for Linux
  
    
 Wish List: (Nice To Have for Future)
   (These are the useful features not included in the assignment requirements)
   - Would like to be able to read or write the instruction set to or from a 
     file capable of handling in-code comments and remarks
   - Would like to add HELP instruction to print out useful information
   - Would like to add more variable types e.g. FLOAT, DOUBLE, BOOL
   - Would like to add more operators e.g. DEC, ASSIGN, ADD, SUB, MUL, DIV,...
   - System wide errors could have higher granularity
   - Would like to add a switch to enable a 'verbose' mode, so all the 
     detail operation results could be dumpted to screen

  

Running my solution:
-------------------
You can run my assignment as follows:

  Use the sli (simple language interpreter) in two modes.

	cd dir_with_my_files
        sli
  or
	cd dir_with_my_files
        sli -f ndpl.txt



IDE/Compiler:	
------------
Dev-C++(Open Source IDE)/gcc and g++ compatible
URL: http://www.bloodshed.net/devcpp.html



Running procedure:
-----------------


Assumptions:
-----------
The sli program is been designed, implemented and tested on 
Windows. However is is been claimed that the compiler is gcc
compatible and the have been limited testing perfored under
Linux (SUSE with Linux Kernel version 2.6.5-7.202.7) but I 
Will suggest for maximum stability run this program under
Windows environment.



Conclusions/Remarks:
-------------------
There are a lot of considerations been put in design and 
implementation of this project to make it flexible and extensible.Hopefully this will create a good basis for future projects. 
However deliberately this expansion support kept to minimume to not jeopardize the current requirements late or low quality delivery.



Errors/Bugs:
-----------
System is been tested in an acceptable level. Extensive
testing need to be develop and performed to detect all
the possible bugs and errors.