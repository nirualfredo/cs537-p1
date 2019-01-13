////////////////////////////////////////////////////////////////////////////////
// Main File: main.c
// This File: printer.h
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

#ifndef PRINTER
#define PRINTER

// This method parses through the options with the process ID that are
// both passed in and then prints them to the screen based on what
// values are specified by the ./537ps command
//
// @return int
int printProcessesInfo(CmdLineArgumentsStruct *options, char *processId);

#endif
