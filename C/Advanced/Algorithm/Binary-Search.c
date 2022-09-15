#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST 0

int Binary_Search(int *dat, int x, int len)
{
	int left = 0, right = 0, middle = 0, times = 0;

	right = len;
	while(left <= right){
		middle = (left + right)/2;
#if TEST
		printf("time %d -- left [%d] right [%d] middle [%d]\n", times+1, left, right, middle);
#endif
		times++;
		if(x == dat[middle]){
			printf("\033[40;32mSuccess\033[0m! Travel Times --> %d\n", times);
			return times;
		}else if(x > dat[middle])
			left = middle + 1;
		else
			right = middle - 1;
	}
	printf("\033[40;31mFailed\033[0m! Travel Times --> %d\nTry for another", times);
	return 0;
}

int main()
{
	int len = 0, x = 0;
	int *a;

	printf("Give the length of array:");
	if(!scanf("%d", &len)){
		printf("\033[40;31mInvalid Input!!\033[0m\n");
		return 0;
	}

	printf("Input num u want to search[0-%d]:", len);
	if(!scanf("%d", &x)){
		printf("\033[40;31mInvalid Input!!\033[0m\n");
		return 0;
	}

	// malloc int array.
	a = (int *)malloc(sizeof(int) * len);
	for(int i = 0; i < len; i++){
		a[i] = i;
	}

	/* There is no other way to get the length of array as param.
	   So just get the length and send as param in function.
	   In some funcs, 'strncpy' they include the length.
	*/
	Binary_Search(a, x, len);
	free(a);
}

