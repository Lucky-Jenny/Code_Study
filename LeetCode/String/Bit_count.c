/*
给定一个非负整数 num。对于 0 ≤ i ≤ num 范围中的每个数字 i ，计算其二进制数中的 1 的数目并将它们作为数组返回。

E.g.
num = 2
--> [ 0 1 1 ]

num = 5
--> [ 0 1 1 2 1 2 ]

[URL]
https://leetcode-cn.com/problems/counting-bits/
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEST 1

int *countBits(int num, int *returnSize)
{
	int i = 0;
	int *x = (int *)malloc(sizeof(int) * (num+2));

	x[0] = 0;
	for(i = 1; i <= num; i++){
		if((i&1) == 0){
			x[i] = x[i/2];
		}else{
			x[i] = x[i-1] + 1;
		}
	}
	*returnSize = num + 1;
	return x;
}

int main()
{
	int *bits;
	int size = 0, n = 50;

	printf("num = %d\n", n);
	bits = countBits(n, &size);
	// print
	printf("[ ");
	for(int j = 0; j <= n; j++){
		printf("%d ", bits[j]);
	}
	printf("]\nsize: %d\n", size);
	
}

