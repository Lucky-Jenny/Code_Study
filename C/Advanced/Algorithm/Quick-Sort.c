#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LEN 10

void Print_Array(int x[])
{
	int i = 0;

	for(i = 0; i< LEN; i++)
		printf("%d ", x[i]);
	printf("\n");
}

int Rand_For_Array(int h[])
{
	int i = 0;

	srand(time(0));
	for(i = 0; i < LEN; i++)
		h[i] = rand()%100;		// generate 0-99 in random
}

/*
	It is a good way to use Divide-and-Conquer Algorithm.
*/
void Quick_Sort(int c[], int head, int tail)
{
	int i = head, j = tail;

	while(i <= j){


	}
}

int main()
{
	int i = 0;
	int a[LEN] = {0};

	Rand_For_Array(a);
	printf("Origin Array:\n");
	Print_Array(a);

	//Quick_Sort(a);

}

