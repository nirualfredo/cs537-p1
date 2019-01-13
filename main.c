////////////////////////////////////////////////////////////////////////////////
// Main File: main.c
// This File: main.c
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

#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "printer.h"
#include "reader.h"

// the main function of the program that will utilize other modules
// for parsing the input, finding valid process ids, and printing out
// the relevant information
int main(int argc, char *argv[]){
  
	CmdLineArgumentsStruct *cmdLineArguments = parseCommandLineInput(argc,argv);
	// verify that there wasn't an error processing the command line args
	if(cmdLineArguments == NULL){
		// error
		return -1;
	}

	// print out information for a single process
	if(cmdLineArguments->pFlag){

		if(cmdLineArguments->processId != NULL){
			// print the process id
			printf("%s: ",cmdLineArguments->processId);
			// print the info related to the process
			if(printProcessesInfo(cmdLineArguments, cmdLineArguments->processId)){
				// error happened while printing
				printf("\n");
				return -1;
			}	  
		}else{
			// since the p option was included there should be a process id
			printf("ERROR: No process ID.\n");
			// error
			return -1;
		}
		
	// print out information for all processes
	}else if(!cmdLineArguments->pFlag){
		// if a process id was entered than there should have been a -p option.
		if(cmdLineArguments->processId != NULL){
			printf("ERROR: No -p option selected.\n");
			// error
			return -1;
		}
		// get a list of all valid process ids to print
		char ** listOfProcessIds = readInListOfProcessIds();

		// index for cycling through the pointer to char pointers
		int i = 0;
		// go through the list of pids
		while(*(listOfProcessIds+i) != NULL){
			// print individual process id
			printf("%s: ",*(listOfProcessIds+i));
			// print the info related to the process
			if(printProcessesInfo(cmdLineArguments, *(listOfProcessIds+i))){
				// error
				printf("\n");
				return -1;
			}
			i++;
		}

	}
}
