CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic
EXEC_NAME=xac
FILES=src/ac.c
LIBS=-lX11 -lXtst -lpthread

.PHONY: all clean

all:
	$(CC) $(CFLAGS) -o $(EXEC_NAME) $(FILES) $(LIBS)

install:
	$(CC) $(CFLAGS) -o /usr/bin/$(EXEC_NAME) $(FILES) $(LIBS)

uninstall:
	rm /usr/bin/$(EXEC_NAME)

clean:
	rm $(EXEC_NAME) $(OBJ_FILES)

