/**********************************
File: ailib.h
Author: John Downs
Date: Wed, Sept 7, 2011

Description: See ailib.h.  Implementation of the functions specified there. 

Credit: See ailib.h

************************************/
#include <stdlib.h>
#include "ailib.h"

void *emalloc(long size) {
  void *p = (void *) malloc(size);     /* request memory */

  if (p == NULL) {            /* quit if request failed */
    printf("Unable to intitialize...out of memory.");
    exit(0);
  }

  return p;

} /* end emalloc */

void openFile(FILE **fileptr, char *filename, char *mode) {
  *fileptr = fopen(filename,mode);       /* open the file */

  if ( !(*fileptr)) {
    printf("ERROR: Failed to open file: %s with mode %s.  Exiting.\n\n",
	   filename, mode);
    exit(0);
  }

} /* end openFile */
