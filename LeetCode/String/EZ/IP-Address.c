#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST 0
#define IP_LEN 16

/*
给定一个只包含数字的字符串，用以表示一个 IP 地址，返回所有可能从s获得的有效IP地址。(可任意顺序)
有效IP--> 4个十进制数，每个数的区间[0,255]，用"."分隔。

E.g. s = "25525511135"
	--> ["255.255.11.135", "255.255.111.35"]
	
	 s = "101023"
	--> ["1.0.10.23", "1.0.102.3", "10.1.0.23", "10.10.2.3", "101.0.2.3"]

[URL]
https://leetcode-cn.com/problems/restore-ip-addresses/
*/

int StrToInt(char *s, int start, int end)
{
	int i = 0, base = 1, num = 0;

	for(i = end; i >= start; i--){
		num += (s[i] - '0') * base;
		base *= 10;
	}
	return num;
}

char **ip_arry;
char *str;
int len = 0, arr_size = 0;
int seg[4] = {0};

void backtrace_ip(int seg_idx, int idx)
{
	int i = 0;

	if(seg_idx == 4){
		/* Must contain all parms in str. */
		if(idx < len)
			return;

		for(i = 0; i < 4; i++){
			if(seg[i] > 255 || seg[i] < 0)
				return;
		}
		char *x = (char *)malloc(sizeof(char) * IP_LEN);
		snprintf(x, IP_LEN, "%d.%d.%d.%d", seg[0], seg[1], seg[2], seg[3]);
		ip_arry[arr_size++] = x;
#if TEST
		printf("%s\tarr_size=%d\n", x, arr_size);
#endif
	}else{
		/* limit len <= 3 */
		for(i = idx; i < idx + 3 && i < len; i++){
			/* Should not leading-0 if len > 1 */
			if(str[idx] == '0' && i > idx)
				return;

			seg[seg_idx] = StrToInt(str, idx, i);
#if TEST
			printf("idx=%d, i=%d\tseg[%d]=%d\n", idx, i, seg_idx, seg[seg_idx]);
#endif
			backtrace_ip(seg_idx + 1, i + 1);
		}
	}
}

char **restoreIpAddresses(char *s, int *returnSize)
{
#if TEST
	printf("strlen:%ld\n", strlen(s));
#endif
	if(strlen(s) < 4 || strlen(s) >12)
		return NULL;

	arr_size = 0;
	ip_arry = (char**)malloc(sizeof(char*) * 64);
	str = s;
	len = strlen(s);
	// start backtrace
	backtrace_ip(0, 0);

	*returnSize = arr_size;
	return ip_arry;
}



static char *test_addr[] = {
	"101023",
	"123456165144",
	"2305442",
	"1234321",
	"0000",
	"123",
	"",
	NULL
};



int main()
{
	int ret_len = 0;
	char *x = NULL;

	for(int a = 0; test_addr[a] != NULL; a++){
		x = test_addr[a];
		char **result;

		ret_len = 0;
		printf("s: %s\n", x);
		result = restoreIpAddresses(x, &ret_len);
		// print
		printf("[ ");
		for(int i = 0; i < ret_len; i++){
			if(i > 0)
				printf(",");
			printf("\"\033[40;32m%s\033[0m\"", result[i]);
			free(result[i]);
		}
		printf(" ]\n");
		free(result);
	}
}


