#include "../include/xac_win.h"
#include "../include/xac_common.h"

#ifndef UNICODE
#define UNICODE
#endif

void *w_autoclick(void *args)
{
	puts("start clicking");

	unsigned long delay = ((win_generic_options *)args)->delay;
	INPUT *input = ((win_generic_options *)args)->input;

	while (1 && ((win_generic_options *)args)->start)
	{
		SendInput(1, input, sizeof(INPUT));
		usleep(delay);
	}

	return NULL;
}

int main_w(int argc, char *argv[])
{
	unsigned long delay = 1000000;
	parseOpt(argc, argv, &delay);

	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	RegisterHotKey(NULL, 1, MOD_CONTROL, VK_F6);

	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP);
	input.mi.mouseData = 0;
	input.mi.dwExtraInfo = NULL;
	input.mi.time = 0;

	win_generic_options wgo = {
		.delay = delay,
		.start = 0,
		.input = &input,
	};

	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.message == WM_HOTKEY)
		{
			puts("command received");
			if (wgo.start)
			{
				wgo.start = 0;
			}
			else
			{
				wgo.start = 1;
				pthread_create(&tid, &attr, w_autoclick, (void *)&wgo);
			}
		}
	}

	UnregisterHotKey(NULL, 1);

	return 0;
}
