/*
 Find the longest substring in which alphabets is not duplicated from a Str.(Show the length)
 E.g. abcabdcaba ----> cabd/abdc 4
*/
#include <stdio.h>
#include <string.h>

#define STR_LEN 128

int Check_No_Duplicate(char *start, char *end)
{
	char *p = start, *q = NULL;

	while(p != end){
		q = p;
		while(q++ != end){
			if(*p == *q)
				return 0;
		}
		p++;
	}
	return 1;
}

char *Find_Longest_Substr(char *s)
{
	int n = 0, k = 1, len = 0;
	char *p = s;
	char *q = p + 1;
	static char substr[STR_LEN] = {0};

	while(p != q && *q != '\0' ){
		if(Check_No_Duplicate(p, q)){
			if(k > len){
				strncpy(substr, p, q-p+1);
				substr[q-p+1] = '\0';
				len = k;
			}
			k++;
			q++;
		}else{
			k--;
			p++;
		}
	}
	return substr;
}

int main()
{
	char str[STR_LEN]={0};
	char *result = NULL;

	printf("Original String: ");
	scanf("%s", str);
	result = Find_Longest_Substr(str);
	
	printf("Original String:   \033[40;33m%s\033[0m\n"
		   "Longest subString: \033[40;33m%s\033[0m\n"
		   "[length] %ld\n", str, result, strlen(result));
}

