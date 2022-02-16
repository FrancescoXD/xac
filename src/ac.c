#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void click(Display *dp, int button) {
    XEvent ev;
    memset(&ev, 0, sizeof(ev));
    ev.xbutton.button = button;
    ev.xbutton.same_screen = True;
    ev.xbutton.subwindow = DefaultRootWindow(dp);

    while (ev.xbutton.subwindow) {
        ev.xbutton.window = ev.xbutton.subwindow;
        XQueryPointer(dp, ev.xbutton.window, &ev.xbutton.root, &ev.xbutton.subwindow, &ev.xbutton.x_root, &ev.xbutton.y_root, &ev.xbutton.x, &ev.xbutton.y, &ev.xbutton.state);
    }

    ev.type = ButtonPress;
    XSendEvent(dp, PointerWindow, True, ButtonReleaseMask, &ev);
    XFlush(dp);
    usleep(1);
}

int main(void) {
    Display *dp = XOpenDisplay(NULL);

    while (True) {
        click(dp, Button1);
        sleep(0.5);
    }

    XCloseDisplay(dp);

    return 0;
}
