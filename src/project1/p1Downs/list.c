/*****************************************************************
*	File: List.c
*	Author: John Downs
*	Date: 9/7/2011
*       Common list functions	
*	Note:  The list data includes a char data item and count
*****************************************************************/


#include <stdlib.h>
#include "ailib.h"
#include "list.h"

//Returns a pointer to a new list node
ListP NewNode(char value) {
	ListP Node = emalloc(sizeof(List));
	Node->Data = value;
	Node->Count = 1;
	Node->Next = NULL;
	return Node;
}

//Returns a pointer to the last item in the list
ListP Tail(ListP L) {
	if (L->Next == NULL)
		return L;
	return Tail(L->Next);
}

//Returns a pointer to the first instance of value in the list
//Returns NULL if value is not found
ListP Find(ListP L, char value) {
	if (L->Data == value)
		return L;
	if (L->Next == NULL)
		return NULL;
	return Find(L->Next, value);
}

//Adds a new node to the end of the list
void Add(ListP L, char value) {
	ListP exists = Find(L, value);
	if (exists)
		exists->Count++;
	else {
		ListP tail = Tail(L)->Next = NewNode(value);
		tail->Data = value;
		tail->Count = 1;
	}
}

//Frees memory for the list
void Free(ListP L) {
	if (L->Next == NULL)
		free(L);
	else {
		Free(L->Next);
		free(L);
	}
}

//Print the attribute/count pairs
void Print(ListP L) {
	if (L->Data == '\0' && L->Next != NULL) //skip head
		Print(L->Next);
	else {
		printf("%c = %i", L->Data, L->Count);
		if (L->Next != NULL) {
			printf(" , ");
			Print(L->Next);
		}
	}			
}

//Array of list constructor
ListP* makeArrayofList(int attrib_ct) {
	int k;
	ListP* Attributes;
	Attributes = emalloc(sizeof(ListP) * attrib_ct);
	for (k = 0; k < attrib_ct; k++)
		Attributes[k] = NewNode('\0');
	return Attributes;
}
