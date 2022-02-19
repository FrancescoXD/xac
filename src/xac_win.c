#include "../include/xac_win.h"
#include "../include/xac_common.h"

#ifndef UNICODE
#define UNICODE
#endif

#define HOTKEY1 1000

void *w_autoclick(void *args)
{
	puts("start clicking");

	unsigned long delay = ((win_generic_options *)args)->delay;

	while (1 && ((win_generic_options *)args)->start)
	{
		SendInput(1, &input, sizeof(INPUT));
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

	RegisterHotKey(NULL, HOTKEY1, MOD_CONTROL, VK_F6);

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

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == HOTKEY1)
		{
			switch (LOWORD(msg.wParam))
			{
			case HOTKEY1:
				if (wgo.start)
				{
					go.start = 0;
				}
				else
				{
					go.start = 1;
					pthread_create(&tid, &attr, w_autoclick, (void *)wgo);
				}
				break;
			}
		}
	}

	return 0;
}
