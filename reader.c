////////////////////////////////////////////////////////////////////////////////
// Main File: main.c
// This File: reader.c
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
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

// buffer & ids
static const int MAX_IDS = 600;
static const int BUFFER= 300;

// values for building file paths
static const char *proc = "/proc/";
static const char *status = "/status";


// This method reads through the list of processes in /proc,
// checks which ones belong to the current user, and then stores
// those processes in an array and returns that array
//
// @return listOfProcessIds
char ** readInListOfProcessIds(){


	DIR *dp;
	struct dirent *entry;
	char *pid;
	int processUid = 0;
	char *read = "r";

	int userUid = getuid();
	
	// a check to see if the directory is valid
	if ((dp = opendir("/proc")) == NULL){
		fprintf(stderr, "cannot open directory");
		return NULL;
	}
	// the while loop that iterates through /proc
	int counter = 0;
	char ** listOfProcessIds;
	listOfProcessIds = (char **) calloc((BUFFER*MAX_IDS), sizeof(char *));
	while((entry = readdir(dp)) != NULL){

		// if the dirent struct holds the pid in d_name
		if(isNumber(entry->d_name)){
			pid = entry->d_name;

			// create filepath to check uid
			char *filePath;
			filePath = calloc((sizeof(proc)+sizeof(pid)+sizeof(status)), sizeof(char));
			strcat(filePath, proc);
			strcat(filePath, pid);
			strcat(filePath, status);
			
			// creates the stat file	
			FILE *status_file;
			status_file = fopen(filePath, read);
			free(filePath);
			if (status_file == 0){
				// empty code since the process doesn't belong to the current user
			}else{
				char *statusParse;
				statusParse = (char *) calloc(BUFFER, sizeof(char *));
				int uidNext = 0;
				while ((fscanf(status_file,"%s",statusParse)) == 1){

					if(uidNext){
						// get uid
						processUid = atoi(statusParse);
						break;
					}
					if(strcmp(statusParse, "Uid:") == 0){
						uidNext = 1;
					}

				}
				free(statusParse);
				// if uid doesn't match add it to the array
				if (userUid == processUid) {
						printf("pid = %s\n",pid);
						*(listOfProcessIds+counter) = pid;
						// keep an index of where to put the process ids
						counter++;
				}
			}
			fclose(status_file);	
		}
	}
	//closedir(dp);
	return listOfProcessIds;
}
