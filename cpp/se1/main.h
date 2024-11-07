/*
  Main entry to this program header file
  Defines system-wide headers required, constants and values
*/

#ifndef _MAIN_H_
#define _MAIN_H_

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

/*
  Define the program constants
*/

//Version
static const float VERSION = 0.2;
//Author
static const char* AUTHOR = "Ara Bedrossian";
//Maximum length of one line of input
static const int MAX_LINE_SIZE = 255;
//Maximum number of instruction lines allowed to input
static const int MAX_LINES = 100;
//maximum number of defined variables i.e. A,B,C,D,E,F,G,H,I,J
static const int MAX_VARIABLES = 10;
//First variable letter i.e. 'A'
static const char FIRST_VARIABLE = 'A';

//NDPL Instruction set and their Tokens
//Copy
static const char* INST_COPY = "COPY";
static const int INST_COPY_TKN = 1;
//INC
static const char* INST_INC = "INC";
static const int INST_INC_TKN = 2;
//Copy
static const char* INST_WHILENE = "WHILENE";
static const int INST_WHILENE_TKN = 3;
//Copy
static const char* INST_ENDWHILE = "ENDWHILE";
static const int INST_ENDWHILE_TKN = 4;
//End
static const char* INST_END = "END";
static const int INST_END_TKN = 5;

//System wide error codes
//No error
static const int ERR_NO = 0;
//General error
static const int ERR_GENERAL = -1;
//Syntax error
static const int ERR_SYNTAX = -2;
//Bad Variable naming
static const int ERR_VARIABLE_NAMING = -3;
//Runtime error
static const int ERR_RUNTIME = -4;

#endif //_MAIN_H_
