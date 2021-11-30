CC := cc
FLAGS := -std=c99 -pedantic -Wall -Wextra -Werror -Wshadow

SRC := main.c
DEST := bf

all:
	$(CC) $(FLAGS) $(SRC) -o $(DEST)

clean:
	-rm $(DEST)
