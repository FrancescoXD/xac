#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    // open the connection
    Display *dpy = XOpenDisplay(NULL);
    int blackColor = XBlackPixel(dpy, DefaultScreen(dpy)); // get black color
    int whiteColor = XWhitePixel(dpy, DefaultScreen(dpy)); // get white color

    // create a window
    Window w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 200, 100, 0, blackColor, whiteColor);
    XSelectInput(dpy, w, StructureNotifyMask);

    XMapWindow(dpy, w); // show the window
    GC gc = XCreateGC(dpy, w, 0, NULL);
    XSetForeground(dpy, gc, whiteColor);
    XSetBackground(dpy, gc, blackColor);

    XDrawPoint(dpy, w, gc, 5, 5);
    XDrawLine(dpy, w, gc, 10, 10, 400, 400);
    XFlush(dpy);

    XEvent e;
    for (;;) {
        XNextEvent(dpy, &e);
        if (e.type == MapNotify) {
            puts("bye!");
            sleep(2);
            break;
        }
    }

    XCloseDisplay(dpy); // close the connection

    return 0;
}