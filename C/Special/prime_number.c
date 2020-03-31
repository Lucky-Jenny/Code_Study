/*
-Author: Alex-dpx	Date: 2020/3/31
-Function:
 Random and filter Prime Numbers of specified length[LEN].
-Debug:
 Set 'TEST' = 1. It can print the process.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define LEN 1024		// specify the length of Large Number
#define END LEN-1

#define COUNT 2		// count of results
#define TEST 0		// for test

int prime[10]={2,3,5,7,11,13,17,19,23,29};

void test_print(char str[], int num)
{
#if TEST
	printf(str, num);
#else
#endif
}

int Judge_Prime(int x[])
{
	int i = 0, m = -1, k = 0, temp = 0, quo = 0;
	char cmd[32];

	if(x[END] == 0 || x[END] == 2 || x[END] == 4	\
		|| x[END] == 5 || x[END] == 6 || x[END] == 8)
		return 0;		// this is obvious.

	for(i = 0; i < 10 ; i++){
		test_print("x / %d= ", prime[i]);		// TEST
		while(++m < LEN){
			temp = temp * 10 + x[m];	//temp --> remainder
			if(prime[i] <= temp){
				k = temp / prime[i];
				temp = temp % prime[i];
			}
			quo = quo *10 + k;		// quo --> quotient
			k = 0;
		}
		test_print("%d..........", quo);			// TEST
		test_print("%d\n", temp);					// TEST
		if(temp == 0 || (quo % 2 == 0 && temp == 0))
			return 0;
		else{
			temp = 0;
			m = -1;
			quo = 0;
		}
	}
	return 1;
}

void Rand_Large_Num(int num[])
{
	int i = 0;
	srand(time(0));
	while(i < LEN){
		num[i] = rand()%10;		// generate 0-9
		i++;
	}
}

void Print_and_Echo_to_File(int x[])
{
	FILE *f;
	int i = 0;
	for(; i < LEN; i++){		// print to console.
		printf("%d", x[i]);
	}
	printf("\n");
	
}

void Find_Prime_Num(int count)
{
	long try = 0, last = 0;
	int got = 0, isPrime = 0;
	int x[LEN] = {1};
	while (got < count || !isPrime ){
		Rand_Large_Num(x);
		// Trasver the last bit 0-9
		for(last = 0; last < 10; last++){
			x[END] = last;
#if TEST
			Print_and_Echo_to_File(x);
			sleep(0.5);
#endif
			if(Judge_Prime(x)){
				printf("Tried for \33[40;31m%ld\033[0m time(s)\n", ++try);
				printf("\033[40;36mSuccess!!\tGet a large prime number:\033[0m\n");
				Print_and_Echo_to_File(x);
				printf("\033[40;33m--------------------------\033[0m\n");
				got++;
				isPrime = 1;
				try = 0;
				sleep(1);
				break;
			}
			else{
				++try;
				isPrime = 0;
			}
		}
	}
}

int main()
{
	Find_Prime_Num(COUNT);	
}
