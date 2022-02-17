#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void autoclick(Display *display, unsigned long delay)
{
	for (int i = 3; i >= 1; --i)
	{
		printf("\r[info] start clicking in... %ds", i);
		fflush(stdout);
		sleep(1);
		if (i == 1)
		{
			printf("\r[info] autoclicker has started.\n");
		}
	}

	while (True)
	{
		XTestFakeButtonEvent(display, Button1, True, CurrentTime);
		XFlush(display);
		XTestFakeButtonEvent(display, Button1, False, CurrentTime);
		XFlush(display);
		usleep(delay);
	}
}

void printHelp(char *app)
{
	printf("=== help page ===\n");
	puts("CTRL + F6 - starts the autoclicker.");
	printf("%s -s 1 - ", app);
	puts("clicks every 1 second.");
	printf("%s -m 100 - ", app);
	puts("clicks every 100 milliseconds.");
	puts("\nexample usage:");
	printf("%s -s 5\n", app);
}

void parseOpt(int argc, char *argv[], unsigned long *delay)
{
	int opt;
	while ((opt = getopt(argc, argv, "hs:m:")) != -1)
	{
		switch (opt)
		{
		case 's':
		{
			*delay = atoi(optarg);
			printf("[info] delay was set to %lus\n", *delay);
			*delay *= 1000000; // seconds
			break;
		}
		case 'm':
		{
			*delay = atoi(optarg);
			printf("[info] delay was set to %lums\n", *delay);
			*delay *= 1000; // milliseconds
			break;
		}
		case 'h':
		{
			printHelp(argv[0]);
			exit(EXIT_FAILURE);
		}
		default:
		{
			printHelp(argv[0]);
			exit(EXIT_FAILURE);
		}
		}
	}
}

int main(int argc, char *argv[])
{
	if (optind >= argc)
	{
		fprintf(stderr, "[error] no argument passed!\n%s -h to see the help page.\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	unsigned long delay = 1000000; // 1 second
	parseOpt(argc, argv, &delay);
	puts("[info] autoclicker app started");
	puts("[info] start the autoclicker with CTRL + F6");

	Display *dp = XOpenDisplay(NULL);
	unsigned int event_mask = KeyPressMask;

	XGrabKey(dp, XKeysymToKeycode(dp, XK_F6), ControlMask, DefaultRootWindow(dp), True, GrabModeAsync, GrabModeAsync);
	XSelectInput(dp, DefaultRootWindow(dp), event_mask);

	XEvent ev;
	while (True)
	{
		while (XPending(dp))
		{
			XNextEvent(dp, &ev);
			switch (ev.type)
			{
			case KeyPress:
			{
				if (XLookupKeysym(&ev.xkey, 0) == XK_F6 && ev.xkey.state & ControlMask)
				{
					autoclick(dp, delay);
				}
				break;
			}
			}
		}
	}

	XCloseDisplay(dp);

	return 0;
}
