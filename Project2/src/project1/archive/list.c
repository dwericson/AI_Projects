#include <stdlib.h>
#include "list.h"
#include "ailib.h"

ListP newList() {
	ListP l = emalloc(sizeof(List));
	l->Data = '\0';
	l->Count = 0;
	l->Next = NULL;
	return l;
}

void Add(ListP l, char data) {
	if (l->Next == NULL)
	{
		ListP N = newList();
		l->Next == N;
		N->Data = data;
		N->Count = 1;
	}
	else
		Add(l->Next, data);
}

ListP Search(ListP l, char item) {
	if (l->Data == item)
		return l;
	else if (l->Next == NULL)
		return NULL;
	else
		return Search(l->Next, item);	
}

void FreeList(ListP l) {
	if (l->Next == NULL)
		free(l);
	else 
	{
		FreeList(l->Next);
		free(l);
	}
}
