/*****************************************************************
*	File: List.h
*	Author: John Downs
*	Date: 9/7/2011
*       Header file for Common list functions	
*	Note:  The list data includes a char data item and count
*****************************************************************/
struct LIST {
	char Data;
	int Count;
	struct LIST* Next;
};

typedef struct LIST List;
typedef List* ListP;

/*********************************************************************************
*	Function: Add 
*	Input: A list to add to and a value to add
*	returns: nothing
*	Description: appends the new value to the end of the list with count 1
**********************************************************************************/
void Add(ListP L, char value);
/*********************************************************************************
*	Function: makeArrayOfList
*	Input: the size of the array
*	returns: a pointer to the array
*	Description: makes an array of Linked Lists
**********************************************************************************/
ListP* makeArrayofList(int attrib_ct);
/*********************************************************************************
*	Function: Find
*	Input: A list to search and a target value
*	returns: A pointer to the node with the target value or null
*	Description: Find an item in the list
**********************************************************************************/
ListP Find(ListP L, char value);
/*********************************************************************************
*	Function: Free
*	Input: A list to free
*	returns: nothing
*	Description: Free the memory used by a linked list
**********************************************************************************/
void Free(ListP L);
/*********************************************************************************
*	Function: Print
*	Input: A list to print
*	returns: nothing
*	Description: Prints the data/count pairs of the list to stdout
**********************************************************************************/
void Print(ListP L);
