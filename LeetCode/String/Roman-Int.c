#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
给定一个罗马数字，将其转换成整数。输入范围: 1-3999。
I    V    X    L    C    D    M
1    5    10   50   100  500  1000

E.g."III" ---> 3
	"IX"  ---> 9
	"LVII"---> 57
	"MCMXCIV" ---> 1994
[URL]
https://leetcode-cn.com/problems/roman-to-integer/
*/

/* Wonderful Solution */
int getValue(char pre, char cur)
{
	/* Give 1 to cur if null */
	if(cur == '\0')
		cur = 'I';

	switch(pre){
		case 'I':
			if(cur == 'V'|| cur == 'X') return -1;
			else if(cur == 'I') return 1;
			else return 0;
		case 'V':
			if(cur == 'I') return 5;
			else return 0;
		case 'X':
			if(cur == 'L'|| cur == 'C') return -10;
			else if(cur == 'D' || cur == 'M') return 0;
			else return 10;
		case 'L':
			if(cur == 'X' || cur == 'V' || cur == 'I') return 50;
			else return 0;
		case 'C':
			if(cur == 'D' || cur == 'M') return -100;
			else return 100;
		case 'D':
			if(cur == 'M') return 0;
			else return 500;
		case 'M': return 1000;
		default: return 0;
	}

}

int RomanToInt(char *s)
{
	int num = 0, tmp = 0;
	char *p = s, *q = p;

	while(*p++ != '\0'){
		if((tmp = getValue(*q, *p)) == 0){
			perror("Invalid Roman String!!\n");
			return 0;
		}else
			num += tmp;
		//printf("[%c][%c]--> %d\n", *q, *p, tmp);

		q = p;
	}

	return num;
}

void Test_RomanToInt()
{
	char str1[] = "MCMXCIV";	// 1994
	char str2[] = "III";		// 3
	char str3[] = "VXLC";		// Error
	char *x = str1;
	int num = 0;

	printf("[String] %s\n", x);
	num = RomanToInt(x);
	printf("--> \033[40;32m%d\033[0m\n", num);

}

/* ------------------------------------------------ */
/*
给定一个整数，将其转为罗马数字。输入范围: 1-3999
I    V    X    L    C    D    M
1    5    10   50   100  500  1000

E.g.  3  ---> "III"
	 49  ---> "XLIX"
	1994 ---> "MCMXCIV"
[URL]
https://leetcode-cn.com/problems/integer-to-roman/
*/

/* 
	!!!  贪心算法 !!!  --> 在当前情况下做最优的处理
	即 在每次循环中，总是减去小于它的最大符号
*/
char *IntToRoman(int num)
{
	char *roman = (char *)malloc(sizeof(char)*32);
	char *p = roman;
	// definition
	int values[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
	char *symbols[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
	int i = 0, tmp = num;

	for(i = 0; i < sizeof(values)/sizeof(values[0]); i++){
		while(values[i] <= tmp){
			tmp -= values[i];
			p += snprintf(p, sizeof(p), "%s", symbols[i]);
		}
	}
	*p = '\0';
	return roman;
}

void Test_IntToRoman()
{
	int n1 = 123;
	int n2 = 49;
	int n3 = 1994;
	int x = n2;
	char *ret = NULL;

	printf("[Num] %d\n", x);
	ret = IntToRoman(x);
	printf("--> \033[40;32m%s\033[0m\n", ret);

	free(ret);
}

int main()
{
	/* Test RomanToInt */
	Test_RomanToInt();
	
	/* Test IntToRoman */
	Test_IntToRoman();
}


