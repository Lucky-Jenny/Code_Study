#include<stdio.h>


int main()
{
  int x=10;
  int n=1;
  while(x--)	// only x=0(false), the loop will end.
		// if while(1), then it is a deadloop.
  {
    printf("Loop-->%d.\n",n);
    n++;
  }
}

