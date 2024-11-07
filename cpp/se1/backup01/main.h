/*
 Main entry to this program header file
 Defines system-wide constants and values
*/

#ifndef _MAIN_H_
#define _MAIN_H_

#include <cstdlib>
#include <iostream>

using namespace std;

/*
 define the program constants
*/

//Version
static const float VERSION = 0.1;
//Maximum length of one line of input
static const int LB_SIZE = 255;
//Maximum number of instruction lines allowed to input
static const int MAX_LINES = 255;
//maximum number of defined variables i.e. A,B,C,D,E,F,G,H,I,J
static const int MAX_VARIABLE_ARRAY_SIZE = 10;
//First variable letter i.e. 'A'
static const char FIRST_VARIABLE = 'A';

//System wide error codes
//No error
static const int ERR_NO = 0;
//General error
static const int ERR_GENERAL = -1;
//Syntax error
static const int ERR_SYNTAX = -2;

#endif //_MAIN_H_
