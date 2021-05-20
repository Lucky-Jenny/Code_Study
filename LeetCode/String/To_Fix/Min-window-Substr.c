/*
给你一个字符串s 、一个字符串t 。返回s中涵盖t所有字符的最小子串。如果不存在，则返回空""。
注意：如果 s 中存在这样的子串，我们保证它是唯一的答案。

E.g. s = "ADOBECODEBANC"  t = "ABC"
---> "BANC"

[URL]
https://leetcode-cn.com/problems/minimum-window-substring/
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST 1

/* can be enhanced later */
int get_mkIndex(char x, char *t)
{
	for(int i = 0; i < strlen(t); i++){
		if(x == t[i]){
			return i;
		}
	}
	return -1;
}

char *minWindow(char *s, char *t)
{
	int s_len = strlen(s), t_len = strlen(t);

	if(s_len == 0 || s_len < t_len)
		return "";

	int ct_mk = 0;			/* count of marked elements */
	int i = 0, j = 1, idx_i = 0, idx_j = 0, move_hd = 0, len = s_len;

	while((idx_i = get_mkIndex(s[i], t)) == -1 && i < s_len)
		i++;
	/* No match, return null */
	if(i == s_len)
		return "";
	/* return s when len=1 */
	if(t_len == 1)
		return t;

	char *tmp = NULL;
	/* Corresponding to t, mark the previous position. */
	int *mark = (int*)malloc(sizeof(int) * t_len);
	memset(mark, -1, sizeof(int) * t_len);

	mark[idx_i] = i;
	ct_mk++;
	j = i;
	while(i <= j && j < s_len){
		j++;
		move_hd = 0;
		if((idx_j = get_mkIndex(s[j], t)) != -1){
			if(mark[idx_j] == -1){
				mark[idx_j] = j;
				ct_mk++;
			}else{
				if(mark[idx_j] == i){
					move_hd = 1;
					mark[idx_j] = j;
				}
			}
		}
		/* marked elemnt is full. */
		if(ct_mk == t_len){
			if(j-i+1 < len){
				len = j-i+1;
				tmp = &s[i];		// pointer --> &arry[n]
				printf("tmp:%s\tlen=%d\n", tmp, len);
			}
			move_hd = 1;
		}
		if(move_hd){
			/*
			 Move i to next mark position.
			  1. Find the top position from mark[];
			  2. If mark[idx_i] = i, set to -1.
				 If mark[idx_i] > j, mark -= i
			*/
			if(mark[idx_i] == i){
				mark[idx_i] = -1;
				ct_mk--;
			}
			i = j;
			for(int a = 0; a < t_len; a++){
				if(mark[a] < i && mark[a] != -1){
					i = mark[a];
					idx_i = a;
				}
			}
		}

#if TEST
		printf("i=%d  j=%d\t ct_mk=%d\t", i, j, ct_mk);
		printf("mark[]: ");
		for(int h = 0; h < t_len; h++)
			printf("%d ", mark[h]);
		printf("  \tidx_i=%d  idx_j=%d\n", idx_i, idx_j);
#endif
		//j++;
	}

	char *str = (char*)malloc(sizeof(char) * (len + 1));

	if(tmp)
		snprintf(str, len+1, "%s", tmp);
	else
		snprintf(str, len+1, "%s", s);

	free(mark);

	return str;
}

// Test
struct Check_Object{
	char *str;
	char *t;
	char *value;
};
typedef struct Check_Object Check_t;

Check_t vld_list[] = {
	{"ADOBECODEBANC", "ABC", "BANC"},
	{"ADOBFCODEBANC", "CDE", "CODE"},
	{"A", "A", "A"},
	{"A", "ABC", ""},
	{"AAA", "A", "A"},
	{"ACB", "ABC", "ACB"},
	{"BBAA", "ABA", "BAA"},		// problem here
	{NULL, NULL, NULL}
};


void Test_minWinStr()
{
	for(int i = 0; vld_list[i].str != NULL; i++){
		printf("s: %s  t: %s\n", vld_list[i].str, vld_list[i].t);
		char *result = minWindow(vld_list[i].str, vld_list[i].t);
		printf("--> \033[40;32m%s\033[0m\t", result);
		if(!strcmp(result, vld_list[i].value))
			printf("\033[40;32mCorrect\033[0m\n");
		else
			printf("\033[40;31mError\033[0m\n");

		if(result != "" && strlen(vld_list[i].t) > 1)
			free(result);
	}
}

int main()
{
	Test_minWinStr();
}


