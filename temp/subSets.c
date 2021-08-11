#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST 0
#define MAX 10


struct Test_SubSet{
	int nums[MAX];
	int nsize;
};
typedef struct Test_SubSet test_subset;

/*
给你一个整数数组nums，数组中的元素互不相同。返回该数组所有可能的子集（幂集）。
注: 子集不能重复。

E.g. nums = [1,2,3]
---> [[],[1],[2],[3],[1,2],[1,3],[2,3],[1,2,3]]

[URL]
https://leetcode-cn.com/problems/subsets/
*/

int nSize = 0, len = 0, idx = 0;	// idx of ret
int **ret;
int *tmp, *num, *retColSize;
/*
  idx_num/idx_col: index of nums / column.
*/
void backtrace_subset(int idx_num, int idx_col)
{
	if(idx_num == nSize || idx_col == len){
		int *x = (int*)malloc(sizeof(int) * len);
		for(int i = 0; i < len; i++){
			if(tmp[i] == -1)
				return;
			x[i] = tmp[i];
		}
		ret[idx] = x;
		retColSize[idx++] = len;

		return;
	}

	for(int i = idx_num; i < nSize; i++){
		tmp[idx_col] = num[i];
#if TEST
		printf("i=%d, idx_col=%d\t", i, idx_col);
		printf("tmp: ");
		for(int a = 0; a < len; a++){
			if(tmp[a] == -1)
				printf("%d ", tmp[a]);
			else
				printf(" %d ", tmp[a]);
		}
		printf("\n");
#endif
		backtrace_subset(i+1, idx_col+1);
		tmp[idx_col] = -1;
	}

}

int **subsets(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
	if(numsSize == 0)
		return NULL;

	/* retSize = 2^n */
	*returnSize = 1;
	for(int i = 0; i < numsSize; i++)
		*returnSize *= 2;

	ret = (int**)malloc(sizeof(int*) * (*returnSize));
	*returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));
	tmp = (int*)malloc(sizeof(int) * (*returnSize));
	memset(tmp, -1, sizeof(int) * (*returnSize));

	idx = 0;
	num = nums;
	retColSize = *returnColumnSizes;
	// NullSet is must.
	ret[idx] = NULL;
	retColSize[idx++] = 0;

	nSize = numsSize;
	for(len = 1; len <= numsSize; len++){
		backtrace_subset(0, 0);
#if TEST
		printf("-------\n");
#endif
	}
	free(tmp);
	return ret;
}

static test_subset set_list[] = {
	{{1, 2, 3}, 3},
	{{1, 2, 2}, 3},
	{{}, 0},
	{{1}, 1},
	{{1, 2, 3, 4, 5}, 5},
	{{}, -1}
};

void Test_subSets()
{
	int ret_size = 0;

	for(int i = 0; set_list[i].nsize != -1; i++){
		int **result;
		int *col_size;

		printf("[ ");
		for(int a = 0; a < set_list[i].nsize; a++)
			printf("%d ", set_list[i].nums[a]);
		printf("]\n");

		result = subsets(set_list[i].nums, set_list[i].nsize, &ret_size, &col_size);
		/* print & free */
		printf("--> \033[40;32m{ ");
		if(result == NULL){
			printf("}\033[0m\n");
			continue;
		}
		for(int a = 0; a < ret_size; a++){
			if(a == 0)	printf("[ ");
			else		printf(",[ ");
			for(int b = 0; b < col_size[a]; b++)
				printf("%d ", result[a][b]);
			printf("]");
			// free
			free(result[a]);
		}
		free(result);
		free(col_size);
		printf(" }\033[0m\n");
	}
}

/*
给你一个整数数组nums，其中可能包含重复元素。返回该数组所有可能的子集（幂集）。
注: 子集不能重复。

E.g. nums = [1,2,2]
---> [[],[1],[2],[1,2],[2,2],[1,2,2]]

[URL]
https://leetcode-cn.com/problems/subsets-ii/
*/

int **subsetsWithDup(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{

}

static test_subset set_nodup_list[] = {
	{{1, 2, 2}, 3},
	{{}, 0},
	{{1}, 1},
	{{1, 2, 3, 3, 2}, 5},
	{{}, -1}
};

void Test_subSets_withDuplcats()
{
	int ret_size = 0;

	for(int i = 0; set_nodup_list[i].nsize != -1; i++){
		int **result;
		int *col_size;

		printf("[ ");
		for(int a = 0; a < set_nodup_list[i].nsize; a++)
			printf("%d ", set_nodup_list[i].nums[a]);
		printf("]\n");

		result = subsets(set_list[i].nums, set_list[i].nsize, &ret_size, &col_size);
		/* print & free */
		printf("--> \033[40;32m{ ");
		if(result == NULL){
			printf("}\033[0m\n");
			continue;
		}
		for(int a = 0; a < ret_size; a++){
			if(a == 0)	printf("[ ");
			else		printf(",[ ");
			for(int b = 0; b < col_size[a]; b++)
				printf("%d ", result[a][b]);
			printf("]");
			// free
			free(result[a]);
		}
		free(result);
		free(col_size);
		printf(" }\033[0m\n");
	}

}

int main()
{
	Test_subSets();
	//Test_subSets_withDuplcats();
}


