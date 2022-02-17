#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void autoclick(Display *d, int delay) {
    for (int i = 3; i >= 1; --i) {
        printf("\r[info] start clicking in... %ds", i);
        fflush(stdout);
        sleep(1);
        if (i == 1) {
            printf("\r[info] autoclicker has started.\n");
        }
    }

	while (True) {
        XTestFakeButtonEvent(d, Button1, True, CurrentTime);
        XFlush(d);
       	XTestFakeButtonEvent(d, Button1, False, CurrentTime);
        XFlush(d);
        sleep(delay);
	}
}

void printHelp(char *app) {
    printf("=== help page ===\n");
    puts("CTRL + F6 - starts the autoclicker.");
    printf("%s -d 1 - ", app);
    puts("clicks every 1 second. This is the default value.");
    puts("\nexample usage:");
    printf("%s -d 0.5\n", app);
}

void parseOpt(int argc, char *argv[], int *delay) {
    int opt;
    while ((opt = getopt(argc, argv, "hd:")) != -1) {
        switch (opt) {
            case 'd': {
                *delay = atoi(optarg);
                printf("[info] delay was set to %ds\n", *delay);
                puts("[info] start the autoclicker with CTRL + F6");
                break;
            }
            case 'h': {
                printHelp(argv[0]);
                exit(EXIT_FAILURE);
            }
            default: {
                printHelp(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (optind >= argc) {
        fprintf(stderr, "[error] no argument passed, %s -h to see the help page.\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    puts("[info] autoclicker app started");
    int delay = 1;
    parseOpt(argc, argv, &delay);

    Display *dp = XOpenDisplay(NULL);
    unsigned int event_mask = KeyPressMask;

    XGrabKey(dp, XKeysymToKeycode(dp, XK_F6), ControlMask, DefaultRootWindow(dp), True, GrabModeAsync, GrabModeAsync);
    XSelectInput(dp, DefaultRootWindow(dp), event_mask);

    XEvent ev;
    while (True) {
        while (XPending(dp)) {
            XNextEvent(dp, &ev);
            switch (ev.type) {
                case KeyPress: {
                    if (XLookupKeysym(&ev.xkey, 0) == XK_F6 && ev.xkey.state & ControlMask) {
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
