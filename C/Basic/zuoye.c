#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LEN 3		// length of interger
#define END LEN-1
#define COUNT 2		// count of results

int prime[10]={2,3,5,7,11,13,17,19,23,29};
int Quick_Multiply(int a,int b,int c)  // quick multiplay 
{
    long long ans=0,res=a;
    while(b){
		if(b&1)
			ans=(ans+res)%c;
		res=(res+res)%c;
		b>>=1;
	}
	return (int)ans;
}
int Quick_Power(int a,int b,int c)     // quick power
{
    int ans=1,res=a;
    while(b){
		if(b&1)
			ans=Quick_Multiply(ans,res,c);
        res=Quick_Multiply(res,res,c);
		b>>=1;
    }
    return ans;
}
int Miller_Rabin(int x[])     // call the algorithm: Miller Rabin
{
    int i = 0, j, k, a, b;
    int s = 0, t = x[END]-1, m = END;
    if(x[END] == 0 || x[END] == 2 || x[END] == 4	\
		|| x[END] == 5 || x[END] == 6 || x[END] == 8)
		return 0;		// this is obvious.
    while(!(t & 1)){		// change it to (2^s)*t
        s++;
        t = x[END-(++i)];
    }
    for(i=0; i<10 && prime[i] < x[m] && m-- > 0;++i)
    {
		while(x[m] == 0) m--;
        a = prime[i];
        b = Quick_Power(a,t,x[m]); 
        for(j=1;j<=s;++j) 
        {
            k=Quick_Multiply(b,b,x[m]);
            if(k==1 && b!=1 && b!=x[m]-1)
              return 1;
            b=k;
        }
        if(b!=1)  return 1;
    }
    return 0;
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
	long try = 0;
	int got = 0, isPrime = 0;
	int x[LEN] = {1};
	while (got < count || !isPrime ){
		Rand_Large_Num(x);
		//Print_and_Echo_to_File(x);	// test
		if(Miller_Rabin(x)){
			printf("Tried for \33[40;31m%ld\033[0m time(s)\n", try);
			printf("\033[40;36mSuccess!!\tGet a large prime number:\033[0m\n");
			Print_and_Echo_to_File(x);
			printf("\033[40;33m--------------------------\033[0m\n");
			got++;
			isPrime = 1;
			try = 0;
			sleep(1);
		}
		else{
			//printf("Not a Prime number!!\n");
			try++;
			isPrime = 0;
		}
	}
}

int main()
{
	Find_Prime_Num(COUNT);	
}
