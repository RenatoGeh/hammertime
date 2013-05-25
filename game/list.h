#ifndef LINKEDLIST
#define LINKEDLIST

#include <stdlib.h>

typedef struct ll LinkedList;
typedef struct nd Node;

struct nd {
	Body *value;
	struct nd *next;
	struct nd *prev;
};

struct ll {
	Node *head, *tail;
	unsigned int size;
	void (*add)(LinkedList*, Body*);
	int (*remove)(LinkedList*, Body*);
	Body* (*get)(LinkedList*, int);
};

static void _list_add(LinkedList* list, Body* b) {
	int n = list->size;

	if(n>1) {
		list->tail->next = (Node*)malloc(sizeof(Node));
		list->tail->next->value = b;
		list->tail->next->next = NULL;
		list->tail->next->prev = list->tail;

		list->tail = list->tail->next;
	} else {
		if(n==0) list->head->value = b;
		else list->tail->value = b;
	}

	list->size++;
}

static int _list_remove(LinkedList* list, Body* b) {
	Node *n = list->head;

	if(n->value==b) {
		list->head = list->head->next;
		list->head->prev = NULL;
		free(n);
		list->size--;
		return 1;
	} else if(list->tail->value==b) {
		list->tail = list->tail->prev;
		free(list->tail->next);
		list->tail->next = NULL;
		list->size--;
		return 1;
	}

	while(n) {
		if(n->value==b) {
			n->prev->next = n->next;
			n->next->prev = n->prev;
			free(n);
			list->size--;
			return 1;
		}
		n = n->next;
	}
	return 0;
}

static Body* _list_get(LinkedList* list, int index) {
	register int i, size = list->size;
	int n = index<=size/2;
	Node *head = n?list->head:list->tail;
	if(n) for(i=0;i<index;i++) head=head->next;
	else for(i=0;i<size-index-1;i++) head=head->prev;
	return head->value;
}

LinkedList* newList() {
	LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
	list->size = 0;
	
	list->tail = (Node*)malloc(sizeof(Node));
	list->tail->next = NULL;
	list->tail->prev = list->head;

	list->head = (Node*)malloc(sizeof(Node));
	list->head->next = list->tail;
	list->head->prev = NULL;

	list->add = intern_add;
	list->remove = intern_remove;
	list->get = intern_get;

	return list;
}

#endif