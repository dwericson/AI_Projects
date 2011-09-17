/* Linked List, recursively defined */
typedef struct _List{
	char Data;
	int Count;
	struct _List *Next;
} List;

typedef List* ListP;

ListP newList();
ListP Search(ListP l, char item); 
void Add(ListP l, char data);
void FreeList(ListP l);

