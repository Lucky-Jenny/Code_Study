#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_FILE "./LX"
#define MD5_FILE "./LX.md5"

void *strupr(char *str)
{
	for(;*str != '\0'; *str++)
	{
		if(*str >= 97 && *str <= 122)
			*str = (*str)-32;
	}
}

char *cat_file(char *name)
{
	int i;
	FILE *fp;
	static char buf[512];

	buf[0] = '\0';

	fp = fopen(name, "r");
	if (fp == NULL)
		return buf;
	fgets(buf, sizeof(buf), fp);
	fclose(fp);

	i = 0;
	while (buf[i] != '\0' && buf[i] != '\r' && buf[i] != '\n')
		i++;
	buf[i] = '\0';

	return buf;
}

int check_md5(char *fileName, char *md5file)
{
	char cmd[128],*value;
	char controlMd5[33],fileMd5[33];

	/* get md5-values from md5 file */
	value=cat_file(md5file);
	strncpy(controlMd5,value,32);
	controlMd5[32]='\0';

	/* get file's md5 */
	sprintf(cmd,"md5sum %s > md5",fileName);
	/* To uppercase: md5sum %s | awk '{print $1}' | tar a-z A-Z > md5 */
	system(cmd);

	value=cat_file("md5");
	strncpy(fileMd5,value,32);
	fileMd5[32]='\0';
	unlink("md5");	// It will rm md5 after killing the process.

	/* Change fileMd5 to uppercase */
	strupr(fileMd5);

	printf("get md5 values from %s:\n%s\n\n", MD5_FILE, controlMd5);
	printf("md5sum %s:\n%s\n\n", CHECK_FILE, fileMd5);

	if( strncmp(controlMd5,fileMd5,32) == 0 )
		return 1;
	else
		return 0;
}


int main()
{
	if(check_md5(CHECK_FILE, MD5_FILE) == 1)
		printf("The same md5 --> The file has not been changed.\n");
	else
		printf("Different md5 --> The file has been changed.\n");	
}

