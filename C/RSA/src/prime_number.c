/*
 This file is copy from alex-dpx, which is useful in RSA by the way.
*/

#include "config.h"

#define PRIME_END PRIME_LEN-1

int prime[10]={2,3,5,7,11,13,17,19,23,29};

/*	// in case that prime number is a huge number.
static struct bigint BN_Prime = {"bn", {0}, 0, 0};
static pBIGINT bn = &BN_Prime;
*/

void test_print(char str[], int num)
{
#if TEST_PRIME
	printf(str, num);
#else
#endif
}

int Judge_Prime(char x[])
{
	int i = 0, m = -1, k = 0, temp = 0, quo = 0;
	char cmd[32];

	if(x[PRIME_END] == 0 || x[PRIME_END] == 2 || x[PRIME_END] == 4	\
		|| x[PRIME_END] == 5 || x[PRIME_END] == 6 || x[PRIME_END] == 8)
		return 0;		// this is obvious.

	for(i = 0; i < 10 ; i++){
		test_print("x / %d= ", prime[i]);		// TEST
		while(++m < PRIME_LEN){
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

void Rand_Large_Num(char num[])
{
	int i = 0;
	srand(time(0));
	while(i < PRIME_LEN){
		num[i] = rand()%10;		// generate 0-9
		i++;
	}
}

void Print_and_Echo_to_File(char x[])
{
	FILE *f;
	int i = 0;
	for(; i < PRIME_LEN; i++){		// print to console.
		printf("%d", x[i]);
	}
	printf("\n");
	
}

unsigned int Find_Prime_Num()
{
	long try = 0, last = 0;
	int i = 0, j = 1, isPrime = 0, num = 0;
	char x[PRIME_LEN] = {1};

	while (!isPrime){
		Rand_Large_Num(x);
		// Trasver the last bit 0-9
		for(last = 0; last < 10; last++){
			x[PRIME_END] = last;
#if TEST_PRIME
			Print_and_Echo_to_File(x);
			sleep(0.5);
#endif
			if(Judge_Prime(x)){
#if TEST_PRIME
				printf("Tried for \033[40;31m%ld\033[0m time(s)\n", ++try);
				printf("\033[40;36mSuccess!!\tGet a large prime number:\033[0m\n");
				Print_and_Echo_to_File(x);
				printf("\033[40;33m--------------------------\033[0m\n");
#endif
				sleep(1);
				isPrime = 1;
				try = 0;
				break;
			}
			else{
				++try;
				isPrime = 0;
			}
		}
	}
	/*  Calculate directly. */
	for(i = PRIME_END; i >= 0; i--){
		num += x[i]*j;
		j *= 10;
	}
	return num;
}

/*
int main()
{
	int num = 0;
	Find_Prime_Num(&num);
	printf("int:%d\n", num);
}
*/

