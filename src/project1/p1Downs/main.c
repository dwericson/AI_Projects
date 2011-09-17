/**********************************
File: main.c
Author: John Downs
Date: Wed, Sept 7, 2011

Description: A program to read attributes and summarize them

************************************/
/*
	TODO: 
		Test with file in ~congdon/Public/AI/Data
		Clean up false counts
		Clean up ending comma in summary	
		Clean up memory leaks!
*/

#include <stdio.h>  
#include <stdlib.h> 
#include <string.h>
#include "list.h"   //Linked list functions
#include "ailib.h"  //emalloc, openFile, getFilenameFromUser

//Function prototypes

/* Reads Attribute and Line Number from file */
int getValue(FILE* in, int offset); 
/* Reads values from the input file and writes to the output file and populates the lists */
void readAttributes(FILE* in, FILE* out, ListP *L, int attrib_ct);

#define LINELEN 80 

int main(int argc, char* argv[])
{
	FILE *in, *out;     /*Input and output files */
	int attributes,     /*Number of attributes per line */
		lines,	    /*Number of data lines in the file */ 
		readlen,    /*Bytes expected by readline */
		k; 	    /*Loop counter */
	char* fileName;     /*Name of file from user */
	ListP *Attributes;  /*Lists of attributes and their counts */

	/*If no argc, get file names*/
	if (argc == 1) {
		fileName = emalloc(256);
		getFilenameFromUser("Input file: ", fileName);
		openFile(&in, fileName, "r"); 
		getFilenameFromUser("Output file: ", fileName);
		openFile(&out, fileName, "w");
		free(fileName);
	}	
	/*Or read them from the command line*/
	else if (argc == 5) {
		openFile(&in, argv[2], "r");
		openFile(&out, argv[4], "w");
	}
	/*Error */
	else {
		fprintf(stderr, "Bad arguments\n");
		exit(1);
	}

	/*Get attribute and line count */
	attributes = getValue(in, 11);
	lines = getValue(in, 6);
	
	/* Make lists of attributes based on info from the file */
	Attributes = makeArrayofList(attributes);

	/* Read each data line*/
	for (k = 0; k < lines; k++) 
		readAttributes(in, out, Attributes, attributes);

	/* Print each attribute summary */
	for (k = 0; k < attributes; k++) 
	{
		printf("Attribute %i: ", k);
		Print(Attributes[k]);
		printf("\n");
		Free(Attributes[k]);
	}
	free(Attributes);
	return(0);	
}

/*********************************************************************************
*	Function: getValue
*	Input: file descriptor to read from, offset of the integer value
*	returns: the integer value read from the file
*	Description: Reads integer value after a character string of known length
**********************************************************************************/
int getValue(FILE* in, int offset) {
	char* fileLine; /* string to hold a line from the file */
	int readlen = LINELEN;	/* best guess at what the line length will be */
	fileLine = emalloc(readlen); 
	int bytesRead = getline(&fileLine, &readlen, in);
	if (bytesRead != -1) { //All is well
		fileLine += offset; /* skip over attributes:  or lines: */
		return atoi(fileLine);
	}
	return -1; /*ERROR */
}


/*********************************************************************************
*	Function: getValue
*	Input: file descriptor to read from, offset of the integer value
*	returns: the integer value read from the file
*	Description: Reads integer value after a character string of known length
**********************************************************************************/
void readAttributes(FILE* in, FILE* out, ListP* L, int attrib_ct) {
	int bytesRead, /*Bytes read by readline */
		j;  /* Loop Counter */
	int readLen = attrib_ct * 2; /*char + comma*/
	char *fileLine, /*String to hold line from input file*/
		*token;	/*Attribute data, 1 at a time*/
	ListP item;     /*Current node*/

	/* Allocate Memory */
	fileLine = emalloc(readLen);
	token = emalloc(sizeof(char));

	/* Read the next line in the file*/
	bytesRead = getline(&fileLine, &readLen, in);
	
	/* Get the first token */
	token = strtok(fileLine, ",");

	/* For each attribute on the line ... */
	for (j = 0; j < attrib_ct; j++) {
		/* Print the attribute to the output file */
		fprintf(out, "%2c", *token);
		/*Is it in the list already? */
		item = Find(L[j], *token);
		if (item) /*It is, add one more */
			item->Count++;
		else /*It isn't, append it to the list */
			Add(L[j], *token);
		/*Get the next token */
		token = strtok(NULL, ","); 
	}
	fprintf(out, "\n");
}


