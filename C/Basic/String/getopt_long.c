#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	static struct option long_options[] = {
		{"help", no_argument, NULL, 'h'},
		{"file", required_argument, NULL, 'f'},
		{"write", required_argument, NULL, 'w'},
		{0, 0, 0, 0}
	};
	static char * const short_options=(char *)"hf:w::";
	// Attention: "w::" if u type '-w xxx', argument will show (null)
	// So u should type '-wxxx', argment will show "xxx"
	int option_index = 0;
	int ret = 0;
	while((ret=getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
	{
		switch(ret){
			case 'h':
				printf("get option:'--help'\n");break;
			case 'f':
				printf("get option:'--file'\n");
				printf("The argument is %s\n", optarg);break;
			case 'w':
				printf("get option:'--write'\n");
				printf("The argument is %s\n", optarg);break;
			default:
				printf("Unknown option");break;

		}
		printf("\n");
	}

}

