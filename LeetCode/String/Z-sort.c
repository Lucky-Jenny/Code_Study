/*
将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。

E.g. s="PAYPALISHIRING"  line=3
 P   A   H   N
 A P L S I I G
 Y   I   R
---> PAHNAPLSIIGYIR

[URL]
https://leetcode-cn.com/problems/zigzag-conversion
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DYNAMIC 1

char *Z_Convert(char *s, int numRows)
{
	int step = numRows-1, chainNum = 0; //步长、链的个数
	int i = 0, row = 0, line = 0;
	char *ret = (char *)malloc(strlen(s)+1);
#if DYNAMIC
	int **arr;
#endif

	if((strlen(s) - numRows) % step == 0)
		chainNum = (strlen(s) - numRows) / step + 1;
	else
		chainNum = (strlen(s) - numRows) / step + 2;

#if DYNAMIC
	/* 动态申请二维数组 */
	arr = (int **)malloc(sizeof(int *) * numRows);
	for(i = 0; i < numRows; i++){
		arr[i] = (int *)malloc(sizeof(int) * chainNum);
		memset(arr[i], 0, sizeof(int) * chainNum);
	}
#else
	int arr[numRows][chainNum];
	memset(arr, 0, sizeof(arr));
#endif

	i = 1;
	while(line < chainNum){
		if(line%2 == 0){
			row = 1;
			while(s[i] && (row < numRows)){
				arr[row][line] = (int)s[i++];
				row++;
			}
		}else{
			row = numRows - 2;
			while(row >= 0 && s[i]){
				arr[row][line] = (int)s[i++];
				row--;
			}
		}
		line++;
	}

	ret[0] = s[0];
	i = 1;
	for(row = 0; row < numRows; row++){
		for(line = 0; line < chainNum; line++){
			if(arr[row][line])
				ret[i++] = (char)arr[row][line];
		}
		free(arr[row]); 	// free -> avoid detected mem leak
	}
	free(arr);				// free

	ret[strlen(s)] = '\0';
	return ret;
}

int main()
{
	char str1[] = "ABCDEFGHIJK";
	char *result = NULL, *x = str1;
	int line = 3;

	printf("[String] %s   line=%d\n", x, line);
	result = Z_Convert(str1, line);
	printf("--> \033[40;32m%s\033[0m\n", result);

	free(result);
}


