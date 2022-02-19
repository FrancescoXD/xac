#include "../include/xac_win.h"
#include "../include/xac_common.h"

int main_w(int argc, char *argv[]) {
	unsigned long delay = 1000000;
	parseOpt(argc, argv, &delay);
	
	return 0;
}
