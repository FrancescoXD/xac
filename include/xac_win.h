#ifndef __XAC_WIN_H__
#define __XAC_WIN_H__

#include <windows.h>

#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
	unsigned long delay;
	int start;
	INPUT *input;
} win_generic_options;

int main_w(int argc, char *argv[]);

#endif
