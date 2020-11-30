#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST 1

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
			printf("Success! Udergoing for \033[40;33m%d\033[0m times!\n", times);
			return times;
		}else if(x > dat[middle])
			left = middle + 1;
		else
			right = middle - 1;
	}
	printf("Failed! Undergoing for \033[40;33m%d\033[0m times!\nTry for another", times);
	return 0;
}

int main()
{
	int i = 0, len = 0, x = 0;
	int *a;

	printf("Give the length of array:");
	scanf("%d", &len);
	// declare as pointer, but use as array.
	a = (int *)malloc(len * sizeof(int));
	for(i = 0; i < len; i++){
		a[i] = i;
	}
#if 0
	for(i = 0; i < len; i++)
		printf("%d ", a[i]);
	printf("\n");
#endif
	printf("Input the number to search:");
	scanf("%d", &x);

	/* There is no other way to get the length of array as param.
	   So just get the length and send as param in function.
	   In some funcs, 'strncpy' they include the length.	*/
	Binary_Search(a, x, len);

	
}

