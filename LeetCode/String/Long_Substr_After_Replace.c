/*
给你一个仅由大写英文字母组成的字符串，你可以将任意位置上的字符替换成另外的字符，总共可最多替换 k 次。在执行上述操作后，找到包含重复字母的最长子串的长度。
注意：字符串长度 和 k 不会超过 104。
E.g. "AABABBA" k=1
---> 4 (第一个B替换为A，形成AAAABBA)

[URL]
https://leetcode-cn.com/problems/longest-repeating-character-replacement
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

int CharactorReplacement(char *s, int k)
{
	int i = 0, index = 0, replace = 0, len = 0, max = 1;
	char *p = s, *q = p;
	int map[27] = {0};
#if DEBUG
	char *buff = (char *)malloc((strlen(s)+1)*sizeof(char));
#endif
	index = (int)*p-64;
	map[index] = 1;
	while(*p != '\0'){
		if(*(++q) == '\0'){
			if((q-p) > len)
				len = q-p;
			break;
		}
		i = (int)*(q)-64;
		map[i]++;
		if(map[i] > map[index])
			index = i;		// mark the most popular char

		replace = (q-p+1)-map[index]; // Len - count(max) = replace times.
#if DEBUG
		strncpy(buff, p, q-p+1);
		buff[q-p+1] = '\0';
		printf("[len]%ld [max_index]%c [count]%d -->%s\n", q-p+1, (char)index+64, map[index], buff);
#endif
		if(replace > k){
			if((q-p) > len)
				len = q-p;
			i = (int)*(p++)-64;
			map[i]--;
		}

	}
	return len;
}

int main()
{
	char str1[] = "AASDABBBB";
	char str2[] = "AABBB";
	char str3[] = "ABBBC";
	char *x = str1;
	int k = 2, ret = 0;

	printf("[String] %s   k=%d\n", x, k);
	ret = CharactorReplacement(x, k);
	printf("ret=%d\n", ret);
}

