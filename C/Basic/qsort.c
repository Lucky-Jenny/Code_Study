#include <stdio.h>
#include <stdlib.h>

int integer[] = {45, 93, 302, 55, 12, 234};
char *words[] = {"orange", "read", "apple", "no", "great", "elephant"};

int cmp_int(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b );
}

int cmp_str(const void* a, const void *b)
{
	return strcmp(a ,b);
}

void Print(int x)		// print in different style
{
	int i = 0;
	for(i=0; i<6; i++){
		if(x)
			printf("%s ", words[i]);
		else
			printf("%d ", integer[i]);
	}
	printf("\n");
}

void Sort(int index)		// 0:int	1:string
{
	int i = 0;
	printf("Before List\n");
	Print(index);
	if(index)
		qsort(words, 6, sizeof(int), cmp_str);
	else
		qsort(integer, 6, sizeof(int), cmp_int);
	printf("\nAfter List:\n");
	Print(index);
}

int main()
{
	Sort(0);
	Sort(1);
}

