#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int integer[] = {45, 93, 302, 55, 12, 234};
const char *words[] = {"orange", "read", "apple", "no", "great", "elephant"};

#define INT_LEN sizeof(integer)/sizeof(int)
#define WORD_LEN sizeof(words)/sizeof(char *)

int cmp_int(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int cmp_str(const void* a, const void *b)
{
	return strcmp(a, b);
}

void Print(int index)
{
	int i = 0;

	if(index){
		for(i = 0; i < WORD_LEN; i++)
			printf("%s ", words[i]);
	}else{
		for(i = 0; i < INT_LEN; i++)
			printf("%d ", integer[i]);
	}
	printf("\n");
}

void Sort_and_Print(int index)		// 0:int	1:string
{
	printf("Before Sort:\n");
	Print(index);
	if(index)
		qsort(words, WORD_LEN, sizeof(char *), cmp_str);
	else
		qsort(integer, INT_LEN, sizeof(int), cmp_int);
	printf("After Sort:\n");
	Print(index);
	printf("--------\n");
}

int main()
{
	Sort_and_Print(0);
	Sort_and_Print(1);
}

