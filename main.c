#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

union Item {
	unsigned char cell;
	char *loop;
};

#include "linkedlist.h"

LinkedList *cells, *loops;

char content[] = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";

int main(void) {
	cells = linkedlist_new();
	loops = linkedlist_new();

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
			case '[':
				if (cells->item.cell == 0) {
					i = strstr(i, "]");
				} else {
					linkedlist_append(loops);
					loops = loops->next;
					loops->item.loop = i;
				}
				break;
			case ']':
				if (cells->item.cell != 0) {
					i = loops->item.loop;
				} else {
					LinkedList *last = loops->previous;
					linkedlist_pop(loops);
					free(loops);
					loops = last;
				}
				break;
		}
	}

	printf("\n");
}
