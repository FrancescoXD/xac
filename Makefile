CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic
EXEC_NAME=xac
FILES=src/xac.c src/xac_linux.c src/xac_win.c
LIBS=-lX11 -lXtst -lpthread

.PHONY: all install uninstall clean

all:
	$(CC) $(CFLAGS) -o $(EXEC_NAME) $(FILES) $(LIBS)

install:
	$(CC) $(CFLAGS) -o /usr/bin/$(EXEC_NAME) $(FILES) $(LIBS)

uninstall:
	rm /usr/bin/$(EXEC_NAME)

clean:
	rm $(EXEC_NAME) $(OBJ_FILES)

