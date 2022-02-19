#ifndef __XAC_LINUX_H__
#define __XAC_LINUX_H__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
	Display *display;
	unsigned long delay;
	Bool start;
} generic_options;

void *autoclick(void *args);
int main_l(int argc, char *argv[]);

#endif
