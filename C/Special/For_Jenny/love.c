#include "Emoji.h"

void Print_love()
{
	char rpsent = EXPRESS;
	int i, j, k;  
	for(i = 0; i < 2; i++)
		printf("\n");
	for(i = 0; i< TAB+14; i++)		printf(" ");
	printf("I");
	for(i = 0; i < 2; i++)
		printf("\n");
	for(i = 1; i <= 3; i++){
		for(j = 0; j < (TAB+7) - 2 * i; j++)	printf(" ");
		for(k = 0; k < 4 * i + 1; k++)			printf("\033[40;31m%c", rpsent);
		for(j = 0; j < 13 - 4 * i; j++)			printf(" ");
		for(k = 0; k < 4 * i + 1; k++)			printf("%c", rpsent);
		printf("\n");
	}
	for(i = 0; i < 3; i++){
		for(j = 0; j < TAB; j++)		printf(" ");
		for(k = 0; k < 29; k++)			printf("%c", rpsent);
		printf("\n");
	}
	for(i = 7; i > 0; i--){
		for(j = 0; j < TAB+15 - 2 * i; j++)		printf(" ");
		for(k = 0; k < 4 * i - 1; k++)			printf("%c", rpsent);
		printf("\n");
	}
	for(i = 0; i < TAB+14; i++)		printf(" ");
	printf("%c\033[0m", rpsent);
	for(i = 0; i < 2; i++)			printf("\n");
    for(j = 0; j < TAB+13; j++) 	printf(" ");
	printf("you\n");
	for(i = 0; i < 2; i++)			printf("\n");
}


int main()
{
	int m = 0;
	Print_love();
	printf("%s\n", love);
}

