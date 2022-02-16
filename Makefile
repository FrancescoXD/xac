CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic
EXEC_NAME=app
FILES=src/ac.c
OBJ_FILES=
LIBS=-lX11 -lXtst

.PHONY: all clean

all:
	$(CC) $(CFLAGS) -o $(EXEC_NAME) $(FILES) $(OBJ_FILES) $(LIBS)

clean:
	rm $(EXEC_NAME) $(OBJ_FILES)

