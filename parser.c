////////////////////////////////////////////////////////////////////////////////
// Main File: main.c
// This File: parser.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include "parser.h"

// this function is used as a way to validate that
// a process id in the type of a char* is indeed a number
int isNumber(char *argument){
	int i = 0;
	// test that each character in the string is a digit
	while(*(argument+i) != '\0'){
		if(!(isdigit(*(argument+i))) ){
			// isn't a number
			return 0;
		}
		i++;
	}
	// is a number
	return 1;
}

// this function will parse out the command line arguments and pass
// back a struct that contains flags for each possible option as well as
// a possible process id
CmdLineArgumentsStruct * parseCommandLineInput(int argc, char *argv[]){

	// set the string of options that are valid. Used as argument for getopt() func
	const char *options =  "p::s::U::S::v::c::";
  
	// hold the selected option
	int option;
 
	// flags to keep track of which options were slected
	//-p
	int pFlag = 0;
	// -p-
	int hyphenpFlag = 0;
	// -s
	int lowsFlag = 0;
	// -s-
	int hyphenlowsFlag = 0;
	// -U
	int upuFlag = 0;
	// -U-
	int hyphenupuFlag = 0;
	// -S
	int upsFlag = 0;
	// -S-
	int hyphenupsFlag = 0;
	// -v
	int vFlag = 0;
	// -v-
	int hyphenvFlag = 0;
	// -c
	int cFlag = 0;
	// -c-
	int hyphencFlag = 0;

	// keep track of the number of options in the command
	int numOfOptions = 0;

	// store the process id if one is specified in the command line arguments
	char *processId = NULL;

	int i = 0;
	while(i < argc){
		// get options from the command line
		option = getopt (argc, argv, options);
		if(option != -1){
			switch(option)
			{

			// -p option
			case 'p':
				//test that there is an extra hyphen
				if((optarg != NULL) && (strcmp(optarg, "-") == 0)){
					// -p- option
					hyphenpFlag = 1;
				}else if((optarg != NULL)){
					//test that the extra argument is a number
					if(isNumber(optarg)){
						processId = optarg;
						pFlag = 1;
					}else{
						printf("error: process ID list syntax error\n");
						// error
						return NULL;
					}
	  			}else{
	    				pFlag = 1;
				}
	  			break;

			// -s option
			case 's':
				if((optarg != NULL) && (strcmp(optarg, "-") == 0)){
					// -s- option
					hyphenlowsFlag = 1;
				}else if((optarg != NULL)){
					printf("error: process ID list syntax error\n");
					// error
					return NULL;
				}else{
					lowsFlag = 1;
				}
				break;

			// -U option
			case 'U':
				if((optarg != NULL) && (strcmp(optarg, "-") == 0)){
					// -U- option
					hyphenupuFlag = 1;
				}else if((optarg != NULL)){
					printf("error: process ID list syntax error\n");
					// error
					return NULL;
				}else{
					upuFlag = 1;
				}
				break;

			// -S option
			case 'S':
				if((optarg != NULL) && (strcmp(optarg, "-") == 0)){
					// -S- option
					hyphenupsFlag = 1;
				}else if((optarg != NULL)){
					printf("error: process ID list syntax error\n");
					// error
					return NULL;
				}else{
					upsFlag = 1;
				}
				break;

			// -v option
			case 'v':
				if((optarg != NULL) && (strcmp(optarg, "-") == 0)){
					// -v- option
					hyphenvFlag = 1;
				}else if((optarg != NULL)){
					printf("error: process ID list syntax error\n");
					// error
					return NULL;
				}else{
					vFlag = 1;
				}
				break;

			// -c option
			case 'c':
				if((optarg != NULL) && (strcmp(optarg, "-") == 0)){
					// -c- option
					hyphencFlag = 1;
				}else if((optarg != NULL)){
					printf("error: process ID list syntax error\n");
					// error
					return NULL;
				}else{
					cFlag = 1;
				}
				break;

			// bad input  
			case '?':
				printf("error: process ID list syntax error\n");
				// error
				return NULL;
				break;

			default:
			break;
			}
		// count the number of options
		numOfOptions++;
		}
		i++;
	}

	// count the number of arguments left that aren't options
	int numOfNonOptionArguments = (argc-numOfOptions)-1;
	// there should only be one argument that isn't an option, the pid
	if(numOfNonOptionArguments == 1){
		// check it's number
		if(isNumber(argv[optind])){
			processId = argv[optind];
		}else{
			// process id should be a number
			printf("ERROR: Process Id is not valid.\n");
			// error
			return NULL;
		}
	}else if(numOfNonOptionArguments > 1){
		// only one process id should be specified
		printf("ERROR: Only one process id should be specified.\n");
		// error
		return NULL;
	}

	// add all the flags to the struct that will be utilized when printing the output
	CmdLineArgumentsStruct *cmdLineArguments;
	cmdLineArguments = (CmdLineArgumentsStruct*) calloc(1, sizeof(processId)+sizeof(CmdLineArgumentsStruct));
	cmdLineArguments->pFlag = pFlag;
	cmdLineArguments->hyphenpFlag = hyphenpFlag;
	cmdLineArguments->lowsFlag = lowsFlag;
	cmdLineArguments->hyphenlowsFlag = hyphenlowsFlag;
	cmdLineArguments->upuFlag = upuFlag;
	cmdLineArguments->hyphenupuFlag = hyphenupuFlag;
	cmdLineArguments->upsFlag = upsFlag;
	cmdLineArguments->hyphenupsFlag = hyphenupsFlag;
	cmdLineArguments->vFlag = vFlag;
	cmdLineArguments->hyphenvFlag = hyphenvFlag;
	cmdLineArguments->cFlag = cFlag;
	cmdLineArguments->hyphencFlag = hyphencFlag;
	cmdLineArguments->processId = processId;

	return cmdLineArguments;
}
