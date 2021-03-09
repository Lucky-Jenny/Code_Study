#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

//The file tests on popen,fgets,strncmp

int main()
{
	int i = 0;
	char cmd[20] = {0}, line[10]= {0};
	int value[4]={0};
	FILE *f = NULL;

	snprintf(cmd, sizeof(cmd), "echo true");	//echo true; echo false
	printf("[cmd] %s\n", cmd);

	if((f = popen(cmd,"r")) != NULL){		//execute cmd | read the stream
		while(fgets(line, sizeof(line), f) != NULL){
			printf("line: %s", line);
			if(!strncmp(line, "true", 4))
				value[i]=4;
			else if(!strncmp(line, "false", 5))
				value[i]=9;
			else
				printf("NULL");
			printf("value[%d]=%d\n", i, value[i]);
			i++;
	}

	pclose(f);
	}
	return 0;
}

