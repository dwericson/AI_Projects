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
*/

#include <stdio.h>  
#include <stdlib.h> 
#include "list.h"   //Linked list functions
#include "ailib.h"  //emalloc

//Function prototypes
ListP* makeArrayofList(int attrib_ct);
int readValue(); 
void getFileHandles(int argc, char *argv[]);
void PrintSummary(ListP *l, int attrib_ct);
void readAttributes(ListP *l, int attrib_ct);

//File handles
FILE *inF, *outF;

int main(int argc, char* argv[])
{
	int attrib_ct, line_ct;
	int k; //loop counters
	ListP *Attributes; 

	//open files
	getFileHandles(argc, argv); 
	//get attributes and line counters
	attrib_ct = readValue();
	line_ct = readValue();
	getc(inF); //eat newline
	//Make array of attributes
	Attributes = makeArrayofList(attrib_ct);

	//read file
	for (k = 0; k < line_ct; k++)
		readAttributes(Attributes, attrib_ct);
	PrintSummary(Attributes, attrib_ct);
}

void readAttributes(ListP *l, int attrib_ct) {
	int j, bytes, bytes_read;
	char* lineptr;
	char* token;
	ListP current;
	bytes = attrib_ct * 2;
	lineptr = emalloc(bytes);
	bytes_read = getline(&lineptr, &bytes, inF);

	//strip commas 
	token = strtok(lineptr, ",");
	for (j = 0; j < attrib_ct; j++)
	{
		//print to file
		fprintf(outF, "%2c", *token);
		//find attribute in list
		//incrememnt counter or add new item	
		current = Search(l[j], *token);
		if (current != NULL)
			current->Count++;
		else
			Add(l[j], *token);
		token = strtok(NULL, ","); //get next attribute
	}
	fprintf(outF, "\n");
}

void getFileHandles(int argc, char *argv[])
{
	char in[256], out[256];
	int OPEN = FALSE;
	int opt;
	if (argc == 1)
	{
		while (!OPEN)
		{
			fputs("Enter the input file> ", stdout); 
			scanf("%s", in);
			inF = fopen(in, "r");
			if (inF != NULL)
				OPEN = TRUE; 
			if (!OPEN)
				puts("Error opening file, please try again");
		}
		fputs("Enter the output file> ", stdout); 
		scanf("%s", out);
		outF = fopen(out, "w");
	}
	else
	{
		inF = fopen(argv[2], "r");
		if (inF == NULL) {
			fprintf(stderr, "Invalid input file");
			exit(1);
		}			
		outF = fopen(argv[4], "w");
	}		
}

int readValue() {
	int val;
	char buf[80];
	fscanf(inF, "%s%i", buf, &val);
	return val;
}

ListP* makeArrayofList(int attrib_ct) {
	int k;
	ListP* Attributes;
	Attributes = emalloc(sizeof(ListP) * attrib_ct);
	for (k = 0; k < attrib_ct; k++)
		Attributes[k] = emalloc(sizeof(ListP));
	return Attributes;
}

void PrintSummary(ListP *l, int attrib_ct) {
	int k;
	ListP current;
	puts("Summary:");
	for (k = 0; k < attrib_ct; k++)
	{
		current = l[k];
		printf("Attribute %3i: ", k);
		while(current != NULL)
		{
			printf(" %c =%2i ,", current->Data, current->Count); 
			current = current->Next;
		}
		printf("\n");
	}
}
