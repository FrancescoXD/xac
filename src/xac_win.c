#include "../include/xac_win.h"
#include "../include/xac_common.h"

#ifndef UNICODE
#define UNICODE
#endif

#define CTRL_F6 1
#define CTRL_Q  2

void *w_autoclick(void *args)
{
	unsigned long delay = ((win_generic_options *)args)->delay;
	INPUT *input = ((win_generic_options *)args)->input;
	
	for (int i = 3; i >= 1; --i)
	{
		printf("\r[info] start clicking in... %d", i);
		fflush(stdout);
		sleep(1);
		if (i == 1)
		{
			printf("\r[info] autoclicker has started.\n");
		}
	}

	while (1 && ((win_generic_options *)args)->start)
	{
		SendInput(1, input, sizeof(INPUT));
		usleep(delay);
	}

	puts("[info] autoclicker has stopped.");

	return NULL;
}

int main_w(int argc, char *argv[])
{
	unsigned long delay = 1000000;
	parseOpt(argc, argv, &delay);
	puts("[info] autoclicker app started.");
	puts("[info] start/stop the autoclicker with CTRL + F6.");
	puts("[info] quit the autoclicker with CTRL + q.");

	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	RegisterHotKey(NULL, CTRL_F6, MOD_CONTROL, VK_F6);
	RegisterHotKey(NULL, CTRL_Q, MOD_CONTROL, 0x51);

	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP);
	input.mi.mouseData = 0;
	input.mi.dwExtraInfo = (ULONG_PTR)NULL;
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
			switch ((int)msg.wParam) {
				case CTRL_F6:
					if (wgo.start)
					{
						wgo.start = 0;
					}
					else
					{
						wgo.start = 1;
						pthread_create(&tid, &attr, w_autoclick, (void *)&wgo);
					}
					break;
				case CTRL_Q:
					goto CLOSE;
					break;
			}
		}
	}

CLOSE:
	UnregisterHotKey(NULL, CTRL_F6);
	UnregisterHotKey(NULL, CTRL_Q);

	puts("[info] autoclicker app stopped.");

	return 0;
}
