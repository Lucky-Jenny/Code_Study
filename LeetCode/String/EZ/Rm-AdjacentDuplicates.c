#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
给出由小写字母组成的字符串S，选择两个相邻且相同的字母，删除它们, 反复执行此操作，直到无法继续删除。

E.g."abbaca" ---> ca
	"sffrfhhy"  ---> srfy

[URL]
https://leetcode-cn.com/problems/remove-all-adjacent-duplicates-in-string/
*/

char *Remove_Duplicates(char *s)
{
	int i = 0, top = -1;
	char *stack = (char *)malloc(sizeof(char) * (strlen(s) + 1));

	// use stack!!
	for(i = 0; i < strlen(s); i++){
		if(top != -1 && s[i] == stack[top])
			stack[top--] = 0;
		else
			stack[++top] = s[i];
	}
	stack[top+1] = '\0';
	return stack;
}

int main()
{
	char s1[] = "abbdssf";
	char s2[] = "gbddbd";
	char s3[] = "abbawe";
	char s4[] = "aabbcc";
	char *result = NULL, *x = s3;

	printf("s: %s\n", x);
	result = Remove_Duplicates(x);
	printf("--> \033[40;32m%s\033[0m\n", result);

	free(result);
}


