////////////////////////////////////////////////////////////////////////////////
// Main File: main.c
// This File: parser.h
// Other Files: main.c / parser.c / reader.c / printer.c / parser.h / reader.h / printer.h / Makefile
// Semester:         CS 537 Fall 2018
//
// Author:           Ethan Lengfeld
// Email:            elengfeld@wisc.edu
// CS Login:         lengfeld
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None
//
//
// Online sources:   None
//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef PARSER
#define PARSER

// struct that keeps track of which options were selected as well as the process id
typedef struct{
  int pFlag;
  int hyphenpFlag;
  int lowsFlag;
  int hyphenlowsFlag;
  int upuFlag;
  int hyphenupuFlag;
  int upsFlag;
  int hyphenupsFlag;
  int vFlag;
  int hyphenvFlag;
  int cFlag;
  int hyphencFlag;
  char *processId;
} CmdLineArgumentsStruct;

// this function is used as a way to validate that
// a process id in the type of a char* is indeed a number
int isNumber(char *argument);

// this function will parse out the command line arguments and pass
// back a struct that contains flags for each possible option as well as
// a possible process id
CmdLineArgumentsStruct * parseCommandLineInput(int argc, char *argv[]);

#endif
