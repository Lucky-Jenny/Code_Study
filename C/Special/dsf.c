#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct DSF_attribute{
	int day;			// day numbers distant of last time you play CS:GO
	int busy;			// busy degree
	int level;		// fight status
}DSF;

typedef struct Fight_status{
	int level;
	char status[256];
}Fstatus;

Fstatus fs[]={
	0, "\033[40;36mAnyone U want to kill will be alive due to ur terrible accuracy.\033[0m\n",
	1, "\033[40;36mU will only get score:40. And we may lose the game.\033[0m\n",
	2, "\033[40;36mHad better not use AWP, because that is no difference with suicide.\033[0m\n",
	3, "\033[40;36mUr status is unstable. Win or not, that is up to u!\033[0m\n",
	4, "\033[40;36mU are in well status. Take P90! Rush them! U will lead us to win!\033[0m\n",
	5, "\033[40;36mIf u take AWP, they will be afraid and hide to avoid ur massacre.\033[0m\n",
	6, "\033[40;36mPlease give mercy to opponents, or they may consider u are cheating!!\033[0m\n",
};

int yes_input(void)
{
	int i = 0;
	char check[32];
YEAH:
	scanf("%s", check);
	if(strncmp(check, "yes" ,3) == 0 || strncmp(check, "y" ,1) == 0)
		i++;
	else if(strncmp(check, "no" ,2) == 0 || strncmp(check, "n" ,1) == 0)
		i =0;
	else{
		printf("\033[40;33mSo naughty my son. Invalid input! Try again!!\033[0m\n");
		goto YEAH;
	}
	return i;
}

int num_input(void)
{
	int j = 0;
	char check[16] = "";
NUM:
	scanf("%s", check);
	if(isdigit(check[0]))
		j = atol(check);
	else{
		printf("\033[40;33mThat is not a number!! My son. Try again!!\033[0m\n");
		goto NUM;
	}
	return j;
}

DSF Traverse_last_several_days(void)
{
	DSF son = {0, 0, 1};
	printf("How many days has dsf not played CS:GO? \033[40;31m(Input day number)\033[0m\n");
	son.day = num_input();
	printf("Does dsf have coffee today? \033[40;31m(y)es or (n)o\033[0m\n");
	son.level += yes_input();
	printf("Is dsf busy recently? \033[40;31m(y)es or (n)o\033[0m\n");
	son.level -=yes_input();	// If u are busy, u will get struggled.
	printf("Whether dsf volunteer to fight today? \033[40;31m(y)es or (n)o\033[0m\n");
	son.level += yes_input();
	return son;
}

int main(){
	// If u new a struct in this func, U cannot use it as parameter in other funcs!! 
	DSF myson = {0, 0, 1};
	printf("\033[40;33mHello, my son!\nThis program is designed to analyze your fight status.\n");
	printf("<(*~*)>\033[0m\n----------------\n");
	myson = Traverse_last_several_days();
	// more time no play, more powerful u are.
	myson.level += myson.day > 3? 3:myson.day;
	printf("level=%d\n", myson.level);	//test
	printf("----------------\n");
	printf("Your fight level:\033[40;33m%d\033[0m\n%s", myson.level, fs[myson.level].status);
}
