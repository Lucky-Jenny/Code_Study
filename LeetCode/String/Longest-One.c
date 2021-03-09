/*
给定一个由若干 0 和 1 组成的数组 A，我们最多可以将 K 个值从 0 变成 1 。
返回仅包含 1 的最长（连续）子数组的长度。

E.g.A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
	---> 6
		[1,1,1,0,0,1,1,1,1,1,1]

	A = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
	---> 10
		[0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1]

[URL]
https://leetcode-cn.com/problems/max-consecutive-ones-iii/
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST 0

int longestOnes(int *A, int ASize, int K)
{
	int i = 0, j = 0, mark = 0, result = 0;

	// if K >= Asize ==> return Asize
	if(K >= ASize)
		return ASize;

	while(j < ASize){
		if(A[j] == 0)
			mark++;
#if TEST
		printf("[%d]-[%d]  len=%d mark=%d\n", i, j, j-i+1, mark);
		for(int s = i; s <= j; s++)
			printf("%d ", A[s]);
		printf("\n");
#endif
		if(mark > K){
			result = (j-i > result)? j-i : result;
			// head move on
			while(i <= j){
				if(A[i++] == 0){
					if(K > 0){
						mark--;
						break;
					}else{
						mark = 0;
					}
				}
			}
		}else{
			result = (j-i+1 > result)? j-i+1 : result;
		}
		// tail move on
		j++;
	}

	return result;
}

int main()
{
	int a1[] = {1,1,1,0,0,0,1,1,1,1};
	int a2[] = {0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1};
	int a3[] = {0,0,0,1};
	int K = 0;
	int *x;
	int length = 0, ret = 0;


	x = a2;
	/*
	  注意：C语言不能通过指针获取所指向的内存大小 !!!
	  解决：从数组获取 (唯一办法)
	*/
	length = sizeof(a2)/sizeof(int);
	//print
#if TEST
	printf("len = %d\n", length);
#endif
	printf("A = [ ");
	for(int i = 0; i < length; i++){
		printf("%d ", x[i]);
	}
	printf("]\tK = %d\n", K);
	
	ret = longestOnes(x, length, K);
	printf("==> \033[40;32m%d\033[0m\n", ret);

}

