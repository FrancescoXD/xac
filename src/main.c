#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>

#include <xdo.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

#define KEY ControlMask

//void print_mouse_cordinates(Display *d, Window *w, int *x, int *y, unsigned int *mask) {
void print_mouse_cordinates(int *x, int *y) {
    //XQueryPointer(d, DefaultRootWindow(d), w, w, x, y, x, y, mask);
    //XGrabPointer(d, DefaultRootWindow(d), False,  *mask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
    xdo_t *hndl = xdo_new(NULL);
    int screen;
    xdo_get_mouse_location(hndl, x, y, &screen);
    xdo_free(hndl);
    printf("x: %d - y: %d\n", *x, *y);
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
    //unsigned int mask;

    XGrabPointer(dpy, root, False, ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
    //int state;
    //XGetInputFocus(dpy, &root, &state);

    // get CTRL + F6
    XSelectInput(dpy, root, event_mask);
    XGrabKey(dpy, XKeysymToKeycode(dpy, XK_F6), KEY, root, True, GrabModeAsync, GrabModeAsync);
    // AnyModifier - no modifier first

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
                print_mouse_cordinates(&root_x, &root_y);
                break;
            }
        }
        }
    }

    XUngrabKey(dpy, XKeysymToKeycode(dpy, XK_F6), KEY, root);
    XUngrabPointer(dpy, CurrentTime);
    XCloseDisplay(dpy);

    return 0;
}