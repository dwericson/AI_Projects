/*****************************************************************************
 File:   p4.c
 Author: Clare Bates Congdon
 Date:   Thu Sep  6 10:43:43 2007

 Description:
 Read info from a file about the height and width of boxes and print this back
 out to a new file with more information.

 This program illustrates:
 1. defining structures
 2. using an array of pointers to structures
 4. allocating memory for the array and for the structures
 4. how to refer to the parts of the structures

 Notes:
 1. run this program with the file boxes.data. You can pick the output file
    name, but boxes.out would be a good choice.
 2. This program uses global variables to sidestep pointers

 Data Structures:
 This program stores information about boxes in an array of pointers to
 structures. Each structure contains information about the box number, height,
 width, and area.
******************************************************************************/

/*****************************************************************************/
/* include files */
#include <stdio.h>   /* standard input and output */
#include <stdlib.h>  /* standard library, including memory allocation */
#include <math.h>    /* math library */

/*****************************************************************************/
/* constants -- no semicolons at the ends of the lines */
#define TRUE 1       
#define FALSE 0
#define STRLEN 100   /* length (in chars) for strings */

/*****************************************************************************
 data structures:
 *****************************************************************************/
typedef struct Box *BoxP; /* pointer to a Box structure */
struct Box {
  int boxnum;             /* line number of this box */
  int height, width;      /* dimensions of the box */
  int area;               /* area of the box */
};

/*****************************************************************************/
/* global variables */
int NumBoxes;    /* the number of boxes read from the file */
BoxP *BoxArray;  /* an array of pointers to boxes */ 

/*****************************************************************************/
/* prototypes */
void readBoxes ();
void printBoxes ();
void freeBoxes ();
void *emalloc(long size);
void openFile(FILE **fileptr, char *filename, char *mode);
BoxP newBox (void);

/*****************************************************************************
 main
******************************************************************************/
int main(int argc, char* argv[]) {

  printf("This program processes data about the height and width of boxes.\n");
 
  readBoxes();      /* read box information from file into array */

  printBoxes();     /* print from the array */

  freeBoxes();      /* free the memory in the array */

  return(0);        /* return a value */

}  /* end main */

/*****************************************************************************
 Function: readBoxes
 Inputs:   none
 Returns:  nothing, but sets array
 Description:
   read info on boxes from the input file into an array of boxes
 *****************************************************************************/
void readBoxes () {

  char infilename[STRLEN];   /* name of input file */
  FILE *infile;              /* input file (for data) */

  int i;                     /* loop counter */
  int height, width;         /* temporary storage for data read from file */

  /* prompt user and read filename */
  printf("Please type the name of the input file:\n");
  printf("  (Hint: it is boxes.data)\n");
  printf("Name of the input file: ");
  scanf("%s", infilename);

  /* open the file for reading */
  openFile(&infile, infilename, "r");

  /* read the number of lines to follow in the file */
  fscanf(infile, "lines: %d", &NumBoxes);

  /* now you know how big the array is -- allocate the memory */
  BoxArray = (BoxP *) emalloc(NumBoxes * sizeof(BoxP));

  /* for each element of the array, read from the file, store the values, and
     calculate the area */
  for (i=0; i<NumBoxes; i++) {
    fscanf(infile, "%d %d", &height, &width);
    BoxArray[i] = newBox();       /* allocate memory for this box */
    BoxArray[i]->boxnum = i;      /* fill in the fields */
    BoxArray[i]->height = height;
    BoxArray[i]->width = width;
    BoxArray[i]->area = height * width;
  } /* end i loop */

  /* close the input file */
  fclose(infile);

} /* end readBoxes */


/*****************************************************************************
 Function: printBoxes
 Inputs:   none
 Returns:  nothing
 Description:
   print out the information stored in the array
 *****************************************************************************/
void printBoxes () {

  char outfilename[STRLEN];  /* name of output file */
  FILE *outfile;             /* output file (for results) */
  int i;                     /* loop counter */

  /* prompt user and read filename */
  printf("Please type the name of the output file: ");
  scanf("%s", outfilename);

  /* open the output file for writing */
  openFile(&outfile, outfilename, "w");

  /* print out each element in the array */
  for (i=0; i<NumBoxes; i++) {
    fprintf(outfile, "box %2d   height %3d   width %3d   area %4d\n",
	    BoxArray[i]->boxnum, BoxArray[i]->height, BoxArray[i]->width, 
	    BoxArray[i]->area);
  } /* end i loop */

  fclose(outfile);

} /* end printBoxes */


/*****************************************************************************
 Function: freeBoxes
 Inputs:   none
 Returns:  nothing
 Description:
   free the memory in the box array
   note that you have to work from the bottom up
     if there were substructure to a box, that would need to be freed first
 *****************************************************************************/
void freeBoxes () {

  int i;                     /* loop counter */

  /* first, free each of the boxes */
  for (i=0; i<NumBoxes; i++) {
    free(BoxArray[i]);
  }

  /* now, you can free the array */  
  free(BoxArray);

} /* end printBoxes */


/*****************************************************************************
 utility functions
 *****************************************************************************/

/*****************************************************************************
 Function: emalloc
 Inputs:   the size of the block of memory needed
 Returns:  a pointer to the block of memory
 Description: calls malloc, but checks for failure
 *****************************************************************************/
void *emalloc(long size) {
  void *p = (void *) malloc(size);     /* request memory */

  if (p == NULL) {            /* quit if request failed */
    printf("Unable to intitialize...out of memory.");
    exit(0);
  }

  return p;

} /* end emalloc */

/*****************************************************************************
 Function: openFile
 Inputs:   the file to open, the file name, mode to open the file
 Returns:  nothing
 Description: opens file in specified mode or issues error message
 *****************************************************************************/
void openFile(FILE **fileptr, char *filename, char *mode) {
  *fileptr = fopen(filename,mode);       /* open the file */

  if ( !(*fileptr)) {
    printf("ERROR: Failed to open file: %s with mode %s.  Exiting.\n\n",
	   filename, mode);
    exit(0);
  }

} /* end openFile */

/*****************************************************************************
 Function: newBox
 Inputs:   none
 Returns:  pointer to the new Box
 Description: allocates and initializes memory or fails with error message
 *****************************************************************************/
BoxP newBox (void) {
  BoxP box;  /* the new object to return */
        
  box = (BoxP) emalloc (sizeof (struct Box));
        
  if (box == NULL) {
    printf("ERROR: emalloc failed for new Box\n");
    exit(0);
  }

  /* initialize fields */
  box->boxnum = 0;
  box->height = 0;
  box->width = 0;
  box->area = 0;

  return (box);

} /* end newBox */

/****** END OF FILE **********************************************************/
