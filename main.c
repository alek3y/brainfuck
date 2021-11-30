#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

union Item {
	unsigned char cell;
	char *loop;
};

#include "linkedlist.h"

LinkedList *cells = NULL;

char content[] = "++.";

int main(void) {
	cells = linkedlist_new();

	for (char *i = content; *i; i++) {
		switch (*i) {
			case '.':
				printf("%c", cells->item.cell);
				break;
			case '+':
				cells->item.cell++;
				break;
			case '-':
				cells->item.cell--;
				break;
			case '>':
				if (cells->next == NULL) {
					linkedlist_append(cells);
				}
				cells = cells->next;
				break;
			case '<':
				if (cells->previous == NULL) {
					linkedlist_prepend(cells);
				}
				cells = cells->previous;
				break;
		}
	}

	printf("\n");
}
