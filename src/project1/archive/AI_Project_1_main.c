/*
	TODO: Write header stuff
		Write list struct
		Make linked list
		Write list functions search, push, nextVal
		Make array of lists
		Parse command line arguments
		Print dataset summary to stdout
		Test with file in ~congdon/Public/AI/Data
*/

#include <stdio.h> 
#define TRUE 1
#define FALSE 0

void getFileHandles(FILE *inF, FILE *outF, int argc, char *argv[])

int main(int argc, char* argv[])
{
	FILE *in, *out;
	char *lineptr, *token;
	int attributes, lines, bytes_read;
	int k,j; //loop counters

	//open files
	getFileHandles(&in, &out, argc, argv); 
	//get attributes and line counter
	fscanf("%s%i%s%i", attributes, lines);

	//read file
	for (k = 0; k < lines; k++)
	{	
		//read line 
		lineptr = NULL;
		bytes_read = getline(&lineptr, 0, in);
		
		//strip commas 
		token = strtok(lineptr, ",");

		for (i = 0; i < attributes, i++)
		{
			//print to file
			fprintf(out, "%2s", token);
			//find attribute in list
			//incrememnt counter or add new item	
			token = strtok(NULL, ","); //get next attribute
		}
		fprintf(out, "\n");
	}
	//print the list
}

void getFileHandles(FILE **inF, FILE **outF, int argc, char *argv[])
{
	char *in, *out;
	int OPEN = FALSE;
	if (argc - 1)
	{
		while (!OPEN)
		{
			fputs("Enter the input file> ", stdout); 
			scanf("%s", in);
			*inF = fopen(in, 'r');
			if (*inF != NULL)
				OPEN = TRUE; 
			if (!OPEN)
				puts("Error opening file, please try again");
		}
		fputs("Enter the output file> ", stdout); 
		scanf("%s", out);
		*outF = fopen(out, 'w');
	}
	else
	{

	}
}
