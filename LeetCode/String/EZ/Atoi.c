#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32 位有符号整数（类似 C/C++ 中的 atoi 函数）。

myAtoi(string s)的算法如下：
1. 读入字符串并丢弃无用的前导空格；
2. 检查下一个字符为正/负，如果两者都不存在，则为正；
3. 读入下一个字符(直到到达下一个非数字字符或结尾)。其余部分将被忽略。
4. 将读入的这些数字转换为整数（即"0032" -> 32）。如果没有读入数字，则整数为 0 。
5. 如果整数数超过 32 位有符号整数范围 [−2^31,  2^31 − 1] ，需要截断这个整数.
	x < −2^31 --> x = −2^31; x > 2^31−1 --> x = 2^31−1;
返回整数作为最终结果。

注意：
本题中的空白字符只包括空格字符 ' ' 。
除前导空格或数字后的其余字符串外，请勿忽略任何其他字符。

E.g. s = "42"  --> 42
	 s = "20212 like" --> 20212
	 s = "word 123"  --> 0
	 s = "-91283477332" --> -2147483648

[URL]
https://leetcode-cn.com/problems/string-to-integer-atoi/
*/

#define POS_MAX 2147483647
#define NEG_MAX -2147483648

int myAtoi(char *s)
{
	int s_len = strlen(s);
	if(s_len == 0)
		return 0;

	long tmp = 0;
	int i = 0, flag = 0, rm_zero = 0, n_len = 0, num = 0;

	for(i = 0; i < s_len; i++){
		if(flag == 0){
			if(s[i] == '-')
				flag = -1;
			else if(s[i] == '+')
				flag = 1;
			else if(s[i] >= '0' && s[i] <= '9')
				flag = 1;
			else if(s[i] == ' ')
				continue;
			else
				break;
		}else{
			if(s[i] < '0' || s[i] > '9')
				break;
		}
		if(s[i] >= '0' && s[i] <= '9'){
			if(!rm_zero && s[i] == '0')
				continue;
			rm_zero = 1;
			tmp = tmp * 10 + (s[i] - '0');
			if(++n_len > 10)
				break;
		}

	}

	if(flag == -1)
		num = (0 - tmp) < NEG_MAX? NEG_MAX: (0 - tmp);
	else
		num = (tmp > POS_MAX)? POS_MAX: tmp;

	return num;
}

struct Test_Atoi{
	char *s;
	int val;
};
typedef struct Test_Atoi test_atoi;

static test_atoi check_list[] = {
	{"-42", -42},
	{"20223", 20223},
	{"  34 with word", 34},
	{"-91283477332", NEG_MAX},
	{"91283477332", POS_MAX},
	{"347733777777777772112244455533", POS_MAX},
	{"3.14159", 3},
	{"  000000000000123", 123},
	{NULL, -1}
};

int main()
{
	int result;

	for(int i = 0; check_list[i].s != NULL; i++){
		printf("s: %s\n", check_list[i].s);
		result = myAtoi(check_list[i].s);
		// print
		if(result == check_list[i].val)
			printf("--> \033[40;32m%d\033[0m\n", result);
		else
			printf("Error!! Should be %d, but return \033[40;31m%d\033[0m\n", check_list[i].val, result);
	}
}


