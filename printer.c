////////////////////////////////////////////////////////////////////////////////
// Main File: main.c
// This File: printer.c
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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "printer.h"
#include "reader.h"

// buffer size
static const int BUFFER = 1000;

// values for building file paths
static const char *proc = "/proc/";
static const char *stat = "/stat";
static const char *statm = "/statm";
static const char *cmdline = "/cmdline";
static const char *read = "r";

// This method parses through the options with the process ID that are
// both passed in and then prints them to the screen based on what
// values are specified by the ./537ps command
//
// @return int
int printProcessesInfo(CmdLineArgumentsStruct *options, char *processId){

	// the values for specified options
	char status = '\0';
	unsigned long int uTime = 0;
	unsigned long int sTime = 0;
	int size = 0;

	char *procAndPid;
	procAndPid = (char *) calloc((sizeof(proc)+sizeof(processId)), sizeof(char));
	strcat(procAndPid, proc);
	strcat(procAndPid, processId);

	// get stat file
	char *statPath;
	statPath = (char *) calloc((sizeof(stat) + sizeof(procAndPid)), sizeof(char));
	strcat(statPath,procAndPid);
	strcat(statPath,stat);

	FILE *stat_file;
	stat_file = fopen(statPath, read);
	free(statPath);
	// get stat file right away becasue there are 3 options that use it
	if (stat_file == 0){
		//fopen returns 0, the NULL pointer, on failure
		perror("Cannot open stat file\n");
		free(procAndPid);
		return -1;
	}else{
		char *statParse;
		statParse = (char *) calloc(BUFFER, sizeof(char));
		int i = 0;
		while ((fscanf(stat_file,"%s",statParse)) == 1){

			// get status
			if(i == 2){
				status = statParse[0];
			}

			// get u time
			if(i == 13){
				uTime = atoi(statParse);
			}

			// get s time
			if(i == 14){
				sTime = atoi(statParse);
				break;
			}
			i++;
		}
		free(statParse);
		fclose(stat_file);
	}
	
	
	// the lowercase s option
	if(options->lowsFlag){
		// print status
		printf("%c ",status);
	}

	// the uppercase U option
	if(options->hyphenupuFlag){
		//utime is printed by default
	}else{
		// print utime
		printf("utime=%lu ",uTime); 
	}

	// the uppercase S option
	if(options->upsFlag){
		// print stime
		printf("stime=%lu ",sTime);
	}

	// the v option
	if(options->vFlag){

		//get statm file
		char *statmPath;
		statmPath = (char *) calloc((sizeof(statm) + sizeof(procAndPid)), sizeof(char));
		strcat(statmPath,procAndPid);
		strcat(statmPath,statm);

		FILE *statm_file;
		statm_file = fopen(statmPath, read);
		free(statmPath);
		if (statm_file == 0){
			//fopen returns 0, the NULL pointer, on failure
			perror("Cannot open statm file\n");
			free(procAndPid);
			return -1;
		}else{
			char *statmParse;
			statmParse = (char *) calloc(BUFFER, sizeof(char));
			int i = 0;
			while ((fscanf(statm_file,"%s",statmParse)) == 1){
				if(i == 0){
					size = atoi(statmParse);
					break;
				}
			}
			free(statmParse);
			fclose(statm_file);
		}
		printf("vmemory=%d ",size);
	}

	// the c option
	if(options->hyphencFlag){
		//cmdline is printed by default
	}else{

		// get cmdline file
		char *cmdlinePath;
		cmdlinePath = calloc((sizeof(cmdline) + sizeof(procAndPid)), sizeof(char));
		strcat(cmdlinePath,procAndPid);
		strcat(cmdlinePath,cmdline);

		FILE *cmdline_file;
		cmdline_file = fopen(cmdlinePath, read);
		free(cmdlinePath);
		if (cmdline_file == 0){
			//fopen returns 0, the NULL pointer, on failure
			perror("Cannot open cmdline file\n");
			free(procAndPid);
			return -1;
		}else{
			char *cmdLineParse;
			cmdLineParse = calloc((BUFFER*2), sizeof(char));
			while ((fscanf(cmdline_file,"%s",cmdLineParse)) == 1){
				// cmd line value is the first value
				printf("[%s]", cmdLineParse);
				break;
			}
			free(cmdLineParse);
			fclose(cmdline_file);
		}
	}
	free(procAndPid);
	printf("\n");
	return 0;
}
