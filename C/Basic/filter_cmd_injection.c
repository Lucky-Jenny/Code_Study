#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST 0

int has_injection(char *cmd){
	char *p = NULL, *q = NULL;
	char buff[64] = {0};
	FILE *fp = NULL;
#if TEST
	printf("# cmd:%s\n", cmd);
#endif
	snprintf(buff, sizeof(buff), "which %s", cmd);
	fp = popen(buff, "r");
	if(fp){
		if(fgets(buff, sizeof(buff), fp))
			return 1;
	}
	return 0;
}


void filter_cmd(char *value)
{
	char *latent = NULL;

	if(latent = strchr(value, ';')){
		if(has_injection(latent + 1))
			*latent = '\0';
	}
	
	if(latent = strchr(value, '|')){
		if(has_injection(latent + 1))
			*latent = '\0';
	}
}


void test_value()
{
	char val[64] = {0};
	char tt[][64] = \
		{"2 ; touch lxx.tmp", \
		"2 ; OL;SEM|TEKI", \
		"5 | touch lll; SEM|TEKI", \
		"3 | OKK ertjiu ; touch ll.tmp;"};

	for(int i = 0; i < 4; i++){
		strncpy(val, tt[i], sizeof(val));
		printf("[str-%d] %s\n", i+1, val);
		filter_cmd(val);
		printf("[flt-%d] \033[40;32m%s\033[0m\n", i+1, val);
		printf("---\n");
	}
}

int main()
{
	test_value();
	return 0;
}

