CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic
EXEC_NAME=xac
FILES=src/xac.c src/xac_linux.c src/xac_common.c
LIBS=-lX11 -lXtst -lpthread
OBJ_FILES=xac_linux.o xac_common.o

.PHONY: all install uninstall clean

all: xac_linux.o xac_common.o
	$(CC) $(CFLAGS) -o $(EXEC_NAME) src/xac.c $(OBJ_FILES) $(LIBS)

xac_linux.o:
	$(CC) $(CFLAGS) -c src/xac_linux.c -o xac_linux.o

xac_common.o:
	$(CC) $(CFLAGS) -c src/xac_common.c -o xac_common.o

install:
	$(CC) $(CFLAGS) -o /usr/bin/$(EXEC_NAME) $(FILES) $(LIBS)

uninstall:
	rm /usr/bin/$(EXEC_NAME)

clean:
	rm $(EXEC_NAME) $(OBJ_FILES)

