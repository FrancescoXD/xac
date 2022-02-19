#include "../include/xac_linux.h"
#include "../include/xac_common.h"

void *autoclick(void *args)
{
	Display *display = ((generic_options *)args)->display;
	unsigned long delay = ((generic_options *)args)->delay;

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

	while (True && ((generic_options *)args)->start)
	{
		XTestFakeButtonEvent(display, Button1, True, CurrentTime);
		XFlush(display);
		XTestFakeButtonEvent(display, Button1, False, CurrentTime);
		XFlush(display);
		usleep(delay);
	}

	puts("[info] autoclicker has stopped.");

	return NULL;
}

int main_l(int argc, char *argv[])
{
	XInitThreads();

	if (optind >= argc)
	{
		fprintf(stderr, "[error] no argument passed!\n%s -h to see the help page.\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	unsigned long delay = 1000000; // 1 second
	parseOpt(argc, argv, &delay);
	puts("[info] autoclicker app started");
	puts("[info] start/stop the autoclicker with CTRL + F6");
	puts("[info] quit the autoclicker with CTRL + q");

	Display *dp = XOpenDisplay(NULL);
	unsigned int event_mask = KeyPressMask;

	/* Setup thread */
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	generic_options go = {
		.delay = delay,
		.display = dp,
		.start = False,
	};

	XGrabKey(dp, XKeysymToKeycode(dp, XK_F6), ControlMask, DefaultRootWindow(dp), True, GrabModeAsync, GrabModeAsync);
	XGrabKey(dp, XKeysymToKeycode(dp, XK_Q), ControlMask, DefaultRootWindow(dp), True, GrabModeAsync, GrabModeAsync);
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
					if (go.start)
					{
						go.start = False;
					}
					else
					{
						go.start = True;
						pthread_create(&tid, &attr, autoclick, (void *)&go);
					}
				}
				if (XLookupKeysym(&ev.xkey, 0) == XK_q && ev.xkey.state & ControlMask)
				{
					puts("[info] autoclicker app stopped");
					exit(EXIT_SUCCESS);
				}
				break;
			}
			}
		}
	}

	XCloseDisplay(dp);

	return 0;
}
