#include <stdio.h>
#include <string.h>

void test_strstr()
{
	char ss[] = "IVXLCDM";
	char tt[] = "CS";
	char *p =tt;
	char tmp[8];

	snprintf(tmp, sizeof(tmp), "%c", *(p++));
	printf("[strstr]-->%s\n", strstr(ss, tmp));
}

int main()
{
	test_strstr();
	return 0;
}

