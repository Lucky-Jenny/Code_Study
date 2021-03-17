#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST 1

/*
给你一个m行n列的矩阵matrix ，请按照"顺时针螺旋"顺序 ，返回矩阵中的所有元素。

E.g.
1. matrix = [[123], [456], [789]]

	1 -> 2 -> 3
	          ↓
	4 -> 5    6
	↑         ↓
	7 <- 8 <- 9
	
[URL]
https://leetcode-cn.com/problems/spiral-matrix/
*/

/*
  matrixSize    -->  line number
  matrixColSize -->  length of every line
*/
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
	int i = 0, idx = 0, up = 0, down = 0, left = 0, right = 0;
	int len = matrixSize * matrixColSize[0];
	int *str;

	down  = matrixSize - 1;
	right = matrixColSize[0] - 1;
	str = (int *)malloc(sizeof(int) * len);

	/* Clockwise-Travel while shrink the matrix. */
	while(up <= down && left <= right){
		// up
		for(i = left; i <= right; i++)
			str[idx++] = matrix[up][i];
		up++;
		// right
		for(i = up; i <= down; i++)
			str[idx++] = matrix[i][right];
		right--;
		// down
		for(i = right; i >= left && up <= down; i--)
			str[idx++] = matrix[down][i];
		down--;
		// left
		for(i = down; i >= up && left <= right; i--)
			str[idx++] = matrix[i][left];
		left++;
	}
	*returnSize = idx;
	return str;
}

#define MAX 10
struct SpOdr{
	int test[MAX][MAX];
	int depth;
	int width;
};
typedef struct SpOdr Test_Spr;

Test_Spr sp_list[] = {
	{{{1,2,3}, {4,5,6}, {7,8,9}}, 3, 3},
	{{{1,2,3,5}, {4,5,6,8}, {7,8,9,3}}, 3, 4},
	{{{11,24,1,77,5}, {5,34,85,16,3}, {77,88,99.11,22}, {1,2,3,4,5}}, 4, 5},
	{{{1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
	  {11,12,13,14,15,16,17,18,19,20},
	  {21,22,23,24,25,26,27,28,29,30},
	  {31,32,33,34,35,36,37,38,39,40},
	  {41,42,43,44,45,46,47,48,49,50}}, 5, 10},
	{{0}, -1, -1}
};

void Test_Spiral_Travel()
{
	int dep = 0, wid = 0, ret_len = 0;

	for(int i = 0; sp_list[i].depth != -1; i++){
		dep = sp_list[i].depth;
		wid = sp_list[i].width;
		// colSize
		int *colSize = (int *)malloc(sizeof(int) * dep);
		for(int j = 0; j < dep; j++)
			colSize[j] = wid;
		// matrix
		int **matrix = (int **)malloc(sizeof(int *) * dep);
		for(int m = 0; m < dep; m++){
			matrix[m] = (int *)malloc(sizeof(int) * wid);
			for(int n = 0; n < wid; n++){
				matrix[m][n] = sp_list[i].test[m][n];
				if(matrix[m][n] > 9)
					printf("%d ", matrix[m][n]);
				else
					printf(" %d ", matrix[m][n]);
			}
			printf("\n");
		}

		int *ret = spiralOrder(matrix, dep, colSize, &ret_len);
		// print
		printf("--> \033[40;32m");
		for(int i = 0; i < ret_len; i++){
			if(i == 0)
				printf("%d", ret[i]);
			else
				printf(",%d", ret[i]);
		}
		printf("\033[0m\n");

		// free
		for(int j = 0; j < dep; j++)
			free(matrix[j]);
		free(matrix);
		free(colSize);
		free(ret);		
	}
}


/*
给你一个正整数n ，生成一个[n x n]正方形矩阵: 包含 1 到 n^2 所有元素,按顺时针顺序螺旋排列。 

E.g. n = 3
--> [[1,2,3], [8,9,4], [7,6,5]]
	1 -> 2 -> 3
	          ↓
	8 -> 9    4
	↑         ↓
	7 <- 6 <- 5

	 n = 1
--> [[1]]

[URL]
https://leetcode-cn.com/problems/spiral-matrix-ii/
*/

int **generateMatrix(int n, int *returnSize, int **returnColumnSizes)
{
	int **matrix;
	int i, right, left, down, up, idx = 1;

	// matrix
	matrix = (int **)malloc(sizeof(int *) * n);
	*returnColumnSizes = (int *)malloc(sizeof(int) * n);
	for(i = 0; i < n; i++){
		matrix[i] = (int *)malloc(sizeof(int) * n);
		/*
		  The priority of [] is higher than *p
			 *x[i]  --> array[i], each contains *x
			(*x)[i] --> pointer *x, point to array[i]
		*/
		(*returnColumnSizes)[i] = n;
	}
	down  = n - 1;
	right = n - 1;
	/* Clockwise-Travel while shrink the matrix. */
	while(up <= down && left <= right){
		// up
		for(i = left; i <= right; i++)
			matrix[up][i] = idx++;
		up++;
		// right
		for(i = up; i <= down; i++)
			matrix[i][right] = idx++;
		right--;
		// down
		for(i = right; i >= left && up <= down; i--)
			matrix[down][i] = idx++;
		down--;
		// left
		for(i = down; i >= up && left <= right; i--)
			matrix[i][left] = idx++;
		left++;
	}
	// value
	*returnSize = n;
	return matrix;
}

#define TEST_MAX 5
void Test_Generate_Matrix()
{
	int n = 0, ret_len = 0;
	int **mtx;

	for(int i = 1; i <= TEST_MAX; i++){
		printf("n = %d\n\033[40;32m", i);

		int *rt_colSize;
		int **mtx = generateMatrix(i, &ret_len, &rt_colSize);
		// print
		for(int m = 0; m < i; m++){
			for(int n = 0; n < i; n++){
				if(mtx[m][n] > 9)
					printf("%d ", mtx[m][n]);
				else
					printf(" %d ", mtx[m][n]);
			}
			printf("\n");
			free(mtx[m]);
		}
		free(mtx);
		free(rt_colSize);
		printf("\033[0m---------\n");
	}
}

int main()
{
	Test_Spiral_Travel();
	Test_Generate_Matrix();

}

