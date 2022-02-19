#ifdef _WIN32
#include "../include/xac_win.h"
#endif

#ifdef linux
#include "../include/xac_linux.h"
#endif

int main(int argc, char *argv[]) {
	if (optind >= argc) {
		fprintf(stderr, "[error] no argument passed!\n%s -h to see the help page.\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	#ifdef _WIN32
		main_w(argc, argv);
	#elif defined(linux)
		main_l(argc, argv);
	#else
		fprintf(stderr, "[error] os not compatible");
	#endif

	return 0;
}

