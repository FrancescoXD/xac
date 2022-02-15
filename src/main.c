#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

#define KEY ControlMask

void print_mouse_cordinates(Display *d, Window *w, int *x, int *y, unsigned int *mask) {
    XQueryPointer(d, DefaultRootWindow(d), w, w, x, y, x, y, mask);
    printf("x: %d - y: %d\n", *x, *y);
}

void switch_event(XEvent *ev, Bool start) {
    switch (ev->type) {
            case KeyPress: {
                if (XLookupKeysym(&ev->xkey, 0) == XK_F6 && ev->xkey.state & KEY) {
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
                //print_mouse_cordinates(dpy, &root, &root_x, &root_y, &mask);
                break;
            }
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
    //int root_x, root_y;
    //unsigned int mask;

    XGrabPointer(dpy, root, False, ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
    int state;
    XGetInputFocus(dpy, &root, &state);

    XSelectInput(dpy, root, event_mask);
    XGrabKey(dpy, XKeysymToKeycode(dpy, XK_F6), KEY, root, True, GrabModeAsync, GrabModeAsync);
    // AnyModifier - no modifier first

    XEvent ev;
    Bool start = False;
    int x11_fd = ConnectionNumber(dpy);
    fd_set in_fds;
    struct timeval tv;

    while (True) {
        FD_ZERO(&in_fds);
        FD_SET(x11_fd, &in_fds);
        tv.tv_usec = 0;
        tv.tv_sec = 1;

        if (select(x11_fd + 1, &in_fds, 0, 0, &tv)) {
            puts("event received!\n");
        } else {
            puts("timer fired!\n");
        }

        while (XPending(dpy)) {
            XNextEvent(dpy, &ev);
            switch_event(&ev, start);
        }
    }

    XCloseDisplay(dpy);

    return 0;
}