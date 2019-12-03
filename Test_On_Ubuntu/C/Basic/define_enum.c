#include <stdio.h>


#define f(x) x*x	//Macro definition does not have parentheses when expanded.
					// f(x+y)=x+y*x+y
//#define f(x) (x)*(x)
					// f(x+y)=(x+y)*(x+y)
enum {
	LX_A=1,		//1
	LX_B,		//2
	LX_C,		//3
	LX_D,		//4
	LX_E		//5
};

int main()
{
	int x,y,z;
	x=4;
	y=2;
	z=f(x+y)+f(y);
	printf("result: z=%d\n",z);
	printf("enum:\nLX_D=%d\n",LX_D);
}

