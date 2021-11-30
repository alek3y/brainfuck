#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

union Item {
	unsigned char cell;
	char *loop;
};

#include "linkedlist.h"

void usage(char *executable) {
	fprintf(stderr,
		"Usage: %s [OPTION] [FILE]\n"
		"Run brainfuck code.\n\n"
		"OPTIONS:\n"
		" -h               print usage\n"
		" -c cmd           program passed in as string\n",
		executable
	);
}

size_t fsize(FILE *file) {
	size_t offset = ftell(file);
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);

	fseek(file, offset, SEEK_SET);
	return size;
}

int main(int argc, char *argv[]) {
	if (argc <= 1) {
		usage(argv[0]);
		return 1;
	}

	char *contents = NULL;
	for (int i = 0; i < argc; i++) {
		char *arg = argv[i];

		if (strcmp("-c", arg) == 0) {
			contents = argv[++i];
		} else if (strcmp("-h", arg) == 0 || strcmp("--help", arg) == 0) {
			usage(argv[0]);
			return 0;
		}
	}

	if (!contents) {
		FILE *file = fopen(argv[1], "r");
		size_t file_size = fsize(file);

		contents = malloc(file_size);
		fread(contents, 1, file_size, file);

		fclose(file);
	}

	LinkedList *cells = linkedlist_new(), *loops = linkedlist_new();

	for (char *i = contents; *i; i++) {
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
