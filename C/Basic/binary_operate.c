#include <stdio.h>

int main()
{
	int x=3;
	int y=(x+2) & ~4;
	printf("y=(%d+2) & ~4\ny=%d\n",x,y);

}
