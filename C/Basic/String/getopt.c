#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int aflag=0, bflag=0, cflag=0;
	int ch;
	printf("opterr:%d\n", opterr);
	printf("-----------------\n");
	// u can use getopt to create a new command which contains option values.
	while((ch = getopt(argc, argv, "a:b:c:")) != -1)
	{
		printf("return ch=%c\n", ch);
		switch (ch)
		{
			case 'a':
				printf("This is option \"-a\"\nIt shows:%s\n",optarg); break;
				// optarg is the value of -a
			case 'b':
				printf("This is option \"-b\"\nIt shows:%s\n",optarg); break;
			case 'c':
				printf("This is option \"-c\"\nIt shows:%s\n",optarg); break;
			default:
				printf("Unknown option: '%s'\n", argv[1]);
		}
	}
}

