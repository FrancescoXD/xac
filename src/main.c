#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    Display *dpy = XOpenDisplay(0);
    Window root = DefaultRootWindow(dpy);

    XGrabPointer(dpy, root, False, ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
    int state;
    XGetInputFocus(dpy, &root, &state);

    XSelectInput(dpy, root, KeyPressMask | ButtonReleaseMask);
    XGrabKey(dpy, XKeysymToKeycode(dpy, XK_F6), AnyModifier, root, True, GrabModeAsync, GrabModeAsync);

    XEvent ev;
    Bool start = False;
    for (;;) {
        XNextEvent(dpy, &ev);
        switch (ev.type) {
            case KeyPress: {
                if (XLookupKeysym(&ev.xkey, 0) == XK_F6) {
                    if (!start) {
                        start = True;
                        puts("started");
                    } else {
                        start = False;
                        puts("stopped");
                    }
                }
                break;
            }
            case ButtonRelease: {
                puts("mouse clicked");
                break;
            }
        }
    }

    XCloseDisplay(dpy);

    return 0;
}