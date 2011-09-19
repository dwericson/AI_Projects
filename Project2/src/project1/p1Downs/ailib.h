/**********************************
File: ailib.h
Author: John Downs
Date: Wed, Sept 7, 2011

Description: A collection of useful library routines for AI development

Credit:  emalloc and openFile by Clare Congdon from p4.c

************************************/
#define TRUE 1
#define FALSE 0


#include <stdio.h>

/*****************************************************************************
 utility functions
 *****************************************************************************/
/*****************************************************************************
 Function: emalloc
 Inputs:   the size of the block of memory needed
 Returns:  a pointer to the block of memory
 Description: calls malloc, but checks for failure
 *****************************************************************************/
void *emalloc(long size);

/*****************************************************************************
 Function: openFile
 Inputs:   the file to open, the file name, mode to open the file
 Returns:  nothing
 Description: opens file in specified mode or issues error message
 *****************************************************************************/
void openFile(FILE **fileptr, char *filename, char *mode);

/*****************************************************************************
 Function: getFilenameFrom User
 Inputs:   query string to display to the user 
 Returns:  string with a file name
 Description: asks user for a file to open
 *****************************************************************************/
void getFilenameFromUser(char* query, char* answer);
