CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic
EXEC_NAME=xac
FILES=src/xac.c src/xac_linux.c src/xac_common.c src/xac_win.c
LIBS=-lX11 -lXtst -lpthread
L_OBJ_FILES=xac_linux.o xac_common.o
W_OBJ_FILES=xac_win.o xac_common.o

.PHONY: linux windows clean

linux: xac_linux.o xac_common.o
	$(CC) $(CFLAGS) -o $(EXEC_NAME) src/xac.c $(L_OBJ_FILES) $(LIBS)

windows: xac_win.o xac_common.o
	$(CC) $(CFLAGS) -o $(EXEC_NAME) src/xac.c $(W_OBJ_FILES) -lpthread

xac_linux.o:
	$(CC) $(CFLAGS) -c src/xac_linux.c -o xac_linux.o

xac_common.o:
	$(CC) $(CFLAGS) -c src/xac_common.c -o xac_common.o

xac_win.o:
	$(CC) $(CFLAGS) -c src/xac_win.c -o xac_win.o

install:
	$(CC) $(CFLAGS) -o /usr/bin/$(EXEC_NAME) $(FILES) $(LIBS)

uninstall:
	rm /usr/bin/$(EXEC_NAME)

clean:
	rm $(EXEC_NAME) $(L_OBJ_FILES) $(W_OBJ_FILES)

