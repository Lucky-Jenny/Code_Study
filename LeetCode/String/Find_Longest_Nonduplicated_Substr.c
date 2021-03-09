/*
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
E.g. abcdabcb
--> 4

[URL]
https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/

*/
#include <stdio.h>
#include <string.h>

#define STR_LEN 128
#define TEST 0

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
		printf("([%c]-->%d \t[sub] %s\n", *(s+end), (int)*(s+end), sub);
#endif
		++end;
		// Conflict when adding new char in map.
		while(map[(int)*(s+end)] != 0){
			map[(int)*(s+start)] = 0;
			++start;
		}

		if((end-start+1) > len){
			len = end - start + 1;
			strncpy(sub, (s+start), end-start+1);
			sub[end-start+1] = '\0';
		}
		map[(int)*(s+end)] = 1;
	}
	return sub;
}

int main()
{
	char str[STR_LEN]={0};
	char *result = NULL;

	printf("Input str: ");
	if(!scanf("%s", str)){
		printf("Invalid Input!!\n");
		return 0;
	}
	result = Get_Longest_Substr(str);

	printf("Original String:   \033[40;33m%s\033[0m\n"
		   "Longest subString: \033[40;32m%s\033[0m\n"
		   "[length] \033[40;32m%ld\033[0m\n", str, result, strlen(result));
}

