#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef unsigned char uint8;
typedef unsigned int uint32;

//First time: encrypt to another code, Second time: recovery the code.

static void calc_magic(uint8 *data, uint32 n)
{
	uint32 *t = (uint32 *)data; //From 32 to 8.
	n >>= 2;					//Length reduce 4 times
	srand((uint32)'X');
	while(n-- > 0)
		*t++ ^= (uint32)rand();
}

void Binary_printf(uint32 t)
{
	if(t)	{Binary_printf(t/2);}
	else	{return; }
	printf("%d",t%2);
}
//You can use this to print the binary datum.
void Print_Binary(uint8 *pdata)
{
	uint8 *pd = pdata;
	int x=0;
	while(*pd){
		x = *pd++;
		Binary_printf(x);
	}
	printf("\n");
}
//This function can print the char of the pointer in loop
void Print_data(uint8 *pd)
{
	while(*pd){
		printf("%c",*pd); 	//The key is to use "%c"
		pd++;
	}
	printf("\n");
}

int main()
{
	char *p = malloc(200);
	uint32 x;
	int i,j;
	i = sprintf(p, "what");
	i = (i + 3) & ~3;	//This make sure i is multiple of 4.

	printf("Origin String:\n");
	Print_data(p);
	Print_Binary(p);
	//magic
	calc_magic(p,i);
	Print_data(p);
	Print_Binary(p);
	//magic
	calc_magic(p,i);
	Print_data(p);
	Print_Binary(p);

	free(p);
}

