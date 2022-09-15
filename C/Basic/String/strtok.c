#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME "./tmp/dmesg.txt"

// Remove all space in correspond context.
char *Rm_Space_in_list()
{
	static char output[1024] = {0};
	char line[128], temp[128], mg_l[64], mg_r[64];
	char *p, *q, *t;
	FILE *fp = NULL;

	if((fp = fopen(FILENAME, "r")) != NULL){
		while(fgets(line, sizeof(line), fp) != NULL){
			if(strstr(line, ":")){
				p = strtok(line, ":");
				q = strtok(NULL, ":");
				t = q - 2;		// *(q-1)=':' *(q-2)=' '
				// first deal left message
				while(*t == ' ') t--;
				strncpy(mg_l, p, t-p);
				mg_l[t-p] = '\0';

				// then deal right message
				while(*q == ' ') q++;
				t = q;
				while(*t != '\0' && *t != '\n') t++;
				strncpy(mg_r, q, t-q);
				mg_r[t-q] = '\0';

				sprintf(temp, "%s:%s\n", mg_l, mg_r);
				strcat(output, temp);
			}
		}
	}
	return output;
}

int main()
{
	char *p = NULL;
	char cmd[32] = {0};

	snprintf(cmd, sizeof(cmd), "cat %s", FILENAME);
	if(system(cmd) == -1)
		return 0;

	printf("------------\n");
	p = Rm_Space_in_list();
	printf("\033[40;32m%s\033[0m", p);
}

