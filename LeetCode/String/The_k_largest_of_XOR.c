#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
给你一个二维矩阵matrix和一个整数k，矩阵大小为 m x n 由非负整数组成。

矩阵中坐标(a, b)的值=所有满足以下条件的元素执行异或运算得到：
  matrix[i][j]    ( 0 <= i <= a < m && 0 <= j <= b < n ）

请你找出 matrix 的所有坐标中第 k 大的值（k 的值从 1 开始计数）。


E.g. matrix = [[5,2], [1,6]]
    k = 1  ---> f(0,1) = 5 XOR 2 = 7
	k = 2  ---> f(0,0) = 5
	k = 3  ---> f(1,0) = 5 XOR 1 = 4
	k = 4  ---> f(1,1) = 5 XRP 2 XPR 1 XPR 6 = 0

[URL]
https://leetcode-cn.com/problems/find-kth-largest-xor-coordinate-value/
*/

void Print_Matrix(int **mtx, int dep, int wid)
{
	printf("- - - - -\n");
	for(int i = 0; i < dep; i++){
		for(int j = 0; j < wid; j++){
			if(mtx[i][j] > 9)
				printf("%d ", mtx[i][j]);
			else
				printf(" %d ", mtx[i][j]);
		}
		printf("\n");
	}
}

int cmp(int *a, int *b)
{
	return *b - *a;		// 递增: a-b     递减: b-a
}

int kthLargestValue(int **matrix, int matrixSize, int * matrixColSize, int k)
{
	int m = matrixSize, n =  matrixColSize[0];
	// num[] for sort.
	int numIndex = 0;
	int *num = (int *)malloc(sizeof(int) * m * n);
	
	/* mtx_r[][] : matrix for record.
	   Set border --> mtx_r[0][y] = 0, mtx_r[x][0] = 0
	   So row+1, col+1
	*/
	int x = m + 1, y = n + 1;
	int **mtx_r = (int **)malloc(sizeof(int *) * x);
	for(int a = 0; a < x; a++){
		mtx_r[a] = (int *)malloc(sizeof(int) * y);
		memset(mtx_r[a], 0, sizeof(int) * y);
	}
	
	for(int i = 1; i <= m; i++){
		for(int j = 1; j <= n; j++){
			mtx_r[i][j] = mtx_r[i-1][j] ^ mtx_r[i][j-1] ^ mtx_r[i-1][j-1] ^ matrix[i-1][j-1];
			num[numIndex++] = mtx_r[i][j];
		}
	}
	Print_Matrix(mtx_r, x, y);
	/*
	 qsort()是stdlib中的标准库函数，排序方式为：快速排序
	 - num: 待排序的数组首地址
	 - numIndex: 数组元素个数
	 - sizeof(): 单个元素的大小，即步长
	 - cmp: 函数指针，用来表示排序递增/递减 
	*/
	qsort(num, numIndex, sizeof(int), cmp);

	// free
	for(int b = 0; b < x; b++)
		free(mtx_r[b]);
	free(mtx_r);
	
	return num[k-1];
}

struct Test_Mtx{
	char *str;
	int row;
	int column;
};
typedef struct Test_Mtx test_mtx;

static test_mtx check_list[] = {
	{"1,2,3,4,5,6,7,8,9", 3, 3},
	{"1,2,3,5,4,5,6,8,7,8,9,3", 3, 4},
	{"11,24,1,77,5,5,34,85,16,3,77,88,99,11,22,1,2,3,4,5", 4, 5},
/*
	{{{1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
	  {11,12,13,14,15,16,17,18,19,20},
	  {21,22,23,24,25,26,27,28,29,30},
	  {31,32,33,34,35,36,37,38,39,40},
	  {41,42,43,44,45,46,47,48,49,50}}, 5, 10},
*/
	{NULL, -1, -1}
};

int StrToInt(char *s)
{
	int ret = 0, base = 1, len = strlen(s);

	for(int i = len -1; i >= 0; i--){
		ret += base * (s[i] - '0');
		base *= 10;
	}
	return ret;
}

#define LEN 64

void Test_kth_Largest_XOR()
{
	int result = 0;
	int rw = 0, col = 0, k = 1;
	char tmp[LEN] = {0};
	char *token = NULL;


	for(int i = 0; check_list[i].row != -1; i++){
		rw = check_list[i].row;
		col = check_list[i].column;

		// Avoid segmentation fault in strtok(), str should not be const.
		strncpy(tmp, check_list[i].str, LEN);
		token = strtok(tmp, ",");

		// create a matrix
		int **matx = (int **)malloc(sizeof(int *) * rw);
		for(int a = 0; a < rw; a++){
			matx[a] = (int *)malloc(sizeof(int) * col);
			for(int b = 0; b < col; b++){
				matx[a][b] = StrToInt(token);
				token = strtok(NULL, ",");
			}
		}
		// Print matrix
		Print_Matrix(matx, rw, col);
		// malloc for colSize
		int *colSize = (int *)malloc(sizeof(int) * rw);
		for(int j = 0; j < rw; j++)
			colSize[j] = col;
		
		result = kthLargestValue(matx, rw, colSize, k);
		printf("--> \033[40;32m%d\033[0m\n", result);


		// free
		for(int x = 0; x < rw; x++)
			free(matx[x]);
		free(matx);
		free(colSize);
	}

}



int main()
{
	Test_kth_Largest_XOR();
}


