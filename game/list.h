#ifndef LINKEDLIST
#define LINKEDLIST

#include <stdlib.h>

typedef struct ll LinkedList;
typedef struct nd Node;

struct nd {
	void *value;
	struct nd *next;
	struct nd *prev;
};

struct ll {
	Node *head, *tail;
	unsigned size;
	int (*add)(LinkedList*, void*);
	void* (*remove)(LinkedList*, int);
	void* (*get)(LinkedList*, int);
	Node* (*getNode)(LinkedList*, int);
	void (*set)(LinkedList*, int, void*);
};

static Node *_list_getNode(LinkedList *list, int index) {
	register int i;
	int left = index <= list->size/2;

	Node *n = left? list->head : list->tail;
	if(left)
		for(i = 0; i < index; i++) n = n->next;
	else 
		for(i = list->size - 1; i > index ; i--) n = n->prev;
	return n;
}

static void _list_set(LinkedList *list, int index, void* e) {
	_list_getNode(list, index)->value = e;
}

static int _list_add(LinkedList* list, void* b) {
	int n = list->size;

	if(n>1) {
		list->tail->next = (Node*)malloc(sizeof(Node));
		list->tail->next->value = b;
		list->tail->next->prev = list->tail;
		list->tail->next->next = NULL;

		list->tail = list->tail->next;
	} else {
		if(n==0) {
			list->head = (Node*) malloc(sizeof(Node));
			list->head->next = NULL;
			list->head->prev = NULL;
			list->head->value = b;
		}
		else {
			list->tail = (Node*) malloc(sizeof(Node));
			list->tail->next = NULL;
			list->tail->prev = list->head;
			list->head->next = list->tail;
			list->tail->value = b;
		}
	}

	return list->size++;
}



void *removeNode(Node *n) {
	void *v = NULL;
	if(!n) return NULL;
	v = n->value;
	if(n->prev)
		n->prev->next = n->next;
	if(n->next)
		n->next->prev = n->prev;
	n->prev = NULL;
	n->next = NULL;
	n->value = NULL;
	free(n);
	return v;
}

static void *_list_remove(LinkedList* list, int index) {
	list->size--;
	return removeNode(_list_getNode(list, index));
}

static void* _list_get(LinkedList *list, int index) {
	return _list_getNode(list, index)->value;
}

LinkedList* newList() {
	LinkedList *list = (LinkedList*) malloc(sizeof(LinkedList));
	list->size = 0;

	list->tail = NULL;
	list->head = NULL;

	list->add = _list_add;
	list->remove = _list_remove;
	list->get = _list_get;
	list->getNode = _list_getNode;
	list->set = _list_set;

	return list;
}

#endif