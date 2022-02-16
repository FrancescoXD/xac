#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

//#include <xdo.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define KEY ControlMask

void print_mouse_cordinates(Display *d, Window *w, int *x, int *y, unsigned int *mask) {
    XQueryPointer(d, DefaultRootWindow(d), w, w, x, y, x, y, mask);
    //XGrabPointer(d, DefaultRootWindow(d), False,  *mask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
    /* xdo_t *hndl = xdo_new(NULL);
    int screen;
    xdo_get_mouse_location(hndl, x, y, &screen);
    xdo_free(hndl); */
    XUngrabPointer(d, CurrentTime);
    XTestFakeButtonEvent(d, Button1, True, CurrentTime); // press
    XTestFakeButtonEvent(d, Button1, False, CurrentTime); // releases
    XGrabPointer(d, *w, False, ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
    printf("x: %d - y: %d\n", *x, *y);
}

void start_autoclicker(Display *display) {
    puts("Starting in 3 seconds...");
    sleep(3);
    while (True) {
        XTestFakeButtonEvent(display, Button1, True, CurrentTime);
        puts("click");
        XTestFakeButtonEvent(display, Button1, False, CurrentTime);
        puts("release");
    }
}

int main(void) {
    Display *dpy = XOpenDisplay(0);

    if (dpy == NULL) {
        fprintf(stderr, "XOpenDisplay error\n");
        exit(EXIT_FAILURE);
    }

    unsigned int event_mask = KeyPressMask | ButtonReleaseMask;

    Window root = DefaultRootWindow(dpy);
    int root_x, root_y;
    unsigned int mask;

    XGrabPointer(dpy, root, False, ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
    //int state;
    //XGetInputFocus(dpy, &root, &state);

    // get CTRL + F6
    XGrabKey(dpy, XKeysymToKeycode(dpy, XK_F6), KEY, root, True, GrabModeAsync, GrabModeAsync);
    // AnyModifier - no modifier first
    XSelectInput(dpy, root, event_mask);

    XEvent ev;
    Bool start = False;
    
    for (;;) {
        while (XPending(dpy)) {
            XNextEvent(dpy, &ev);
            switch (ev.type) {
            case KeyPress: {
                if (XLookupKeysym(&ev.xkey, 0) == XK_F6 && ev.xkey.state & KEY) {
                    if (!start) {
                        start = True;
                        puts("started");
                        start_autoclicker(dpy);
                    } else {
                        start = False;
                        puts("stopped");
                    }
                }
                XUngrabKey(dpy, XKeysymToKeycode(dpy, XK_F6), KEY, root);
                break;
            }
            case ButtonRelease: {
                puts("mouse clicked");
                print_mouse_cordinates(dpy, &root, &root_x, &root_y, &mask);
                break;
            }
        }
        }
    }

    XCloseDisplay(dpy);

    return 0;
}