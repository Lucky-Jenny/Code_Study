#include <stdio.h>
#include <string.h>

#define STR_LEN 128
#define TEST 1

/*
 Use ASCII code to mark whether the code is exist.
 If start char out, set map[x]=0
*/
char *Get_Longest_Substr(char *s)
{
	int start = 0, end = 0, len = 0;
	char map[256] = {0};
	static char sub[STR_LEN] = {0};

	map[(int)*(s+start)] = 1;
	while(*(s+end) != 0){
#if TEST
		printf("(s+end)[%c]-->%d \t", *(s+end), (int)*(s+end));/////
#endif
		len = len>(end-start+1)?len:(end-start+1);
		++end;
		// Conflict when adding new char in map.
		while(map[(int)*(s+end)] != 0){
			map[(int)*(s+start)] = 0;
			++start;
		}
		strncpy(sub, (s+start), end-start+1);
		sub[end-start+1] = '\0';
		printf("[sub] %s\n", sub);
		map[(int)*(s+end)] = 1;
	}
	return sub;
}

int main()
{
	char str[STR_LEN]={0};
	char *result = NULL;

	printf("Original String: ");
	scanf("%s", str);
	result = Get_Longest_Substr(str);

	printf("Original String:   \033[40;33m%s\033[0m\n"
		   "Longest subString: \033[40;33m%s\033[0m\n"
		   "[length] %ld\n", str, result, strlen(result));
}

