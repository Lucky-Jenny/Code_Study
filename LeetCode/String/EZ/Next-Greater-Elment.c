/*
给定一个循环数组（最后一个元素的下一个元素是数组的第一个元素），输出每个元素的下一个更大元素。
定义更大元素: 当前数字为x，按数组循环遍历，找到x之后的第一个比它更大的数。如果不存在，则输出 -1。

E.g. [ 1, 2, 1 ]
---> [ 2, -1, 2 ]     1 -> 2   2-> -1   1-> 2

[URL]
https://leetcode-cn.com/problems/next-greater-element-ii/
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST 0

int *nextGreaterElements(int *num, int numSize, int *returnSize)
{
	int *arry;
	int i = 0, x = 0;

	arry = (int *)malloc(sizeof(int) * (numSize + 1));
	memset(arry, -1, sizeof(int) * (numSize + 1));

	for(x = 0; x < numSize; x++){
		i = (x+1) % numSize;
		while(i != x){
			if(num[x] < num[i]){
				arry[x] = num[i];
				break;
			}
			i = (i+1) % numSize;
		}
#if TEST
		printf("num[%d] %d\t arry[%d] %d\n", x, num[x], x, arry[x]);
#endif
	}
	*returnSize = numSize;

	return arry;
}

void Print_Int_Arry(int *s, int len, int color)
{
	printf("[ \033[40;%dm", color);
	for(int i = 0; i < len; i++){
		printf("%d ", s[i]);
	}
	printf("\033[0m]\n");
}

int main()
{
	int t1[] = {5, 4, 3, 2, 1};
	int t2[] = {1, 6, 0, 8, 2, 9, 3};
	int rt_size = 0, len = 0;
	int *x = NULL, *ret = NULL;

	x = t1;
	len = sizeof(t1) / sizeof(int);

	ret = nextGreaterElements(x, len, &rt_size);

	printf("arr ");
	Print_Int_Arry(x, len, 0);
	printf("--> ");
	Print_Int_Arry(ret, rt_size, 32);

	free(ret);
}


