#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TEST_FILE "./LX"
#define MD5_FILE "./LX.md5"
#define TMP_FILE "./MD5.txt"

void *strupr(char *str)
{
	for(;*str != '\0'; *str++){
		if(*str >= 97 && *str <= 122)
			*str = (*str)-32;
	}
}

char *cat_file(char *name)
{
	int i = 0;
	FILE *fp = NULL;
	static char buf[512] = {0};

	if((fp = fopen(name, "r")) == NULL)
		return buf;

	if(fgets(buf, sizeof(buf), fp) == NULL)
		printf("Read failed from %s!!\n", name);
	fclose(fp);

	while (buf[i] != '\0' && buf[i] != '\r' && buf[i] != '\n')
		i++;
	buf[i] = '\0';

	return buf;
}

void check_md5(char *test_file, char *md5_file)
{
	char *value;
	char cmd[128], md5_sum[64], md5_from_file[64];

	/* get md5-values from md5 file */
	value = cat_file(md5_file);
	strncpy(md5_from_file, value, 32);
	md5_from_file[32]='\0';

	/* md5sum get value */
	sprintf(cmd,"md5sum %s  > %s", test_file, TMP_FILE);
	/* Uppercase: md5sum %s | awk '{print $1}' | tar a-z A-Z  */

	if(system(cmd) == -1)
		return;

	value = cat_file(TMP_FILE);
	strncpy(md5_sum, value, 32);
	md5_sum[32]='\0';
	unlink(TMP_FILE);	// It will rm md5 after killing the process.

	/* Uppercase */
	strupr(md5_sum);
	strupr(md5_from_file);

	printf("MD5 values from %s:\n%s\n", md5_file, md5_from_file);
	printf("MD5 values from md5sum:\n%s\n\n", md5_sum);

	if(!strncmp(md5_sum, md5_from_file,32))
		printf("The same md5 --> The file has not been changed.\n");
	else
		printf("Different md5 --> The file has been changed.\n");	
}


int main()
{
	check_md5(TEST_FILE, MD5_FILE);
}

