#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void autoclick(Display *d) {
	puts("running...");
	sleep(2);
	puts("stop sleep");
	for (int i = 0; i < 50; ++i) {
		printf("%d", i);
		fflush(stdout);
        	XTestFakeButtonEvent(d, Button1, True, CurrentTime);
        	XFlush(d);
       		XTestFakeButtonEvent(d, Button1, False, CurrentTime);
        	XFlush(d);
	}
	puts("after");
}

int main(void) {
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
                        puts("started autoclicker...");
                        autoclick(dp);
                    }
                    break;
                }
            }
        }
    }

    XCloseDisplay(dp);

    return 0;
}
