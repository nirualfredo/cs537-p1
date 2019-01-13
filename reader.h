////////////////////////////////////////////////////////////////////////////////
// Main File: main.c
// This File: reader.h
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

#ifndef READER
#define READER

// This method reads through the list of processes in /proc,
// checks which ones belong to the current user, and then stores
// those processes in an array and returns that array
//
// @return listOfProcessIds
char ** readInListOfProcessIds();

#endif
