#include "../include/xac_common.h"

void printHelp(void)
{
	printf("=== help page ===\n");
	puts("Hot Keys:");
	puts("CTRL + F6 - starts/stops the autoclicker.");
	puts("CTRL + q - closes the autoclicker.");
	puts("\nArguments:");
	printf("xac -s 1 - ");
	puts("clicks every 1 second.");
	printf("xac -m 100 - ");
	puts("clicks every 100 milliseconds.");
	puts("\nexample usage:");
	printf("xac -s 5\n");
}

void parseOpt(int argc, char *argv[], unsigned long *delay)
{
	int opt;
	while ((opt = getopt(argc, argv, "hs:m:")) != -1)
	{
		switch (opt)
		{
		case 's':
		{
			*delay = atoi(optarg);
			printf("[info] delay was set to %lus\n", *delay);
			*delay *= 1000000; // seconds
			break;
		}
		case 'm':
		{
			*delay = atoi(optarg);
			printf("[info] delay was set to %lums\n", *delay);
			*delay *= 1000; // milliseconds
			break;
		}
		case 'h':
		{
			printHelp();
			exit(EXIT_FAILURE);
		}
		default:
		{
			printHelp();
			exit(EXIT_FAILURE);
		}
		}
	}
}
