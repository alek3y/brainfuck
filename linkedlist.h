#pragma once

typedef struct LinkedList {
	union Item item;
	struct LinkedList *previous, *next;
} LinkedList;

LinkedList *linkedlist_new() {
	return calloc(1, sizeof(LinkedList));
}

void linkedlist_append(LinkedList *self) {
	LinkedList *node = self;
	while (node->next != NULL) {
		node = node->next;
	}
	node->next = linkedlist_new();
	node->next->previous = node;
}

void linkedlist_prepend(LinkedList *self) {
	LinkedList *node = self;
	while (node->previous != NULL) {
		node = node->previous;
	}
	node->previous = linkedlist_new();
	node->previous->next = node;
}
