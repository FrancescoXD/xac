#include "../include/xac_win.h"
#include "../include/xac_common.h"

#ifndef UNICODE
#define UNICODE
#endif

void* test_click(void *args) {
	return NULL;
}

int main_w(int argc, char *argv[]) {
	unsigned long delay = 1000000;
	parseOpt(argc, argv, &delay);

	while (1){
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP);
		input.mi.mouseData = 0;
		input.mi.dwExtraInfo = NULL;
		input.mi.time = 0;
		SendInput(1, &input, sizeof(INPUT));
		puts("clicked");
		usleep(1000000);
	}

	return 0;
}
