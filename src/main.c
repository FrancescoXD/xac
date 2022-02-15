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

    // get input from root
    Window root = XDefaultRootWindow(dpy);
    unsigned int modifiers = ControlMask | ShiftMask;
    int keycode = XKeysymToKeycode(dpy, XK_F6);
    Bool owner_events = False;
    int pointer_mode = GrabModeAsync;
    int keyboard_mode = GrabModeAsync;
    XGrabKey(dpy, keycode, modifiers, root, owner_events, pointer_mode, keyboard_mode);
    XGrabKey(dpy, 72, modifiers, root, owner_events, pointer_mode, keyboard_mode);

    //XSelectInput(dpy, w, StructureNotifyMask);
    XSelectInput(dpy, w, ExposureMask | ButtonPressMask | KeyPressMask);

    XMapWindow(dpy, w);
    GC gc = XCreateGC(dpy, w, 0, NULL);
    XSetForeground(dpy, gc, whiteColor);
    XSetBackground(dpy, gc, blackColor);

    XDrawPoint(dpy, w, gc, 5, 5);
    XDrawLine(dpy, w, gc, 10, 10, 400, 400);
    XFlush(dpy);

    XEvent e;
    for (;;) {
        XNextEvent(dpy, &e);
        switch (e.type) {
            case Expose: {
                puts("ciao");
                break;
            }
            case ButtonPress: {
                puts("cliccato");
                break;
            }
            case KeyPress: {
                puts("f6");
                XUngrabKey(dpy, keycode, modifiers, root);
                break;
            }
        }
    }

    XCloseDisplay(dpy);

    return 0;
}