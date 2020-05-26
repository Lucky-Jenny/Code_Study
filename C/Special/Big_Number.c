#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_LEN 1024
#define TEST_BN 0

typedef struct  bigint{
	char name[32];
	char num[MAX_LEN];		// save in 'char', show in 'int'
	int sign;				// symbol: 1-->positive; -1-->negative
	int digit;				// length of this BN
}*pBIGINT;

enum METHOD{
	ADD,		// Addition
	SUB,		// Subtraction
	MUL,		// Multiplication
	DIV,		// Division
	FAC,		// Factorial
	SQRT,		// Square Root
};

/*
 function: printf all values of struct bigint
*/
void BN_print(pBIGINT bn)
{
	int i = 0;

	printf("----print \033[40;33m%s\033[0m----\n"
		"sign->%d, digit=%d\n",bn->name, bn->sign, bn->digit);
	/* Reverse the print order */
	for(i = bn->digit-1; i >= 0; i--)
		printf("%d", bn->num[i]);
	printf("\n------\n");
}

/*
 function: compare n1 and n2
 return: n1 = n2 ---> 0
 both >0, n1 > n2 ---> 2 (both < 0, |n1| > |n2| ---> -2)
 both >0, n1 < n2 ---> 1 (both < 0, |n1| < |n2| ---> -1)
 n1>0 n2<0, |n1| > |n2| --->  6		|n1| < |n2| ---> 3
 n1<0 n2>0, |n1| > |n2| ---> -6		|n1| < |n2| ---> -3

*/
int BigIntCompare(pBIGINT n1, pBIGINT n2)
{
	int i = 0, sbl = 1;

	// First compare sign
	if(n1->sign != n2->sign){
		if(n1->sign == 1)
			sbl = 3;
		else
			sbl = -3;
	}else{
		if(n1->sign < 0)
			sbl = -1;
	}

	if(n1->digit > n2->digit)
		return  (2 * sbl);
	else if(n1->digit < n2->digit)
		return (1 * sbl);
	/* Compare from top bit to low bit */
	for(i = n1->digit-1; i >= 0; i--){
		if(n1->num[i] > n2->num[i])
			return (2 * sbl);
		else if(n1->num[i] < n2->num[i])
			return (1 * sbl);
	}
	return 0;
}

/*
 func: joint bn2 values(p1, p2) tothe tail of bn1
		[bn1: 4,6,2,3	bn2: 8,5,9,0,1,4,2,2]
		BNjoint(bn1, bn2, 3, 6) ------> bn1: 4,6,2,3,0,1,4,2
 Note: Not include name and sign
*/
int BNjoint(pBIGINT bn1, pBIGINT bn2, int p1, int p2)
{
	int i = 0, j = 0;

	//bn1->sign = bn2->sign;
	j = bn1->digit;
	for(i = p1; i <= p2; i++)
		bn1->num[j++] = bn2->num[i];	
	bn1->digit += p2 - p1 + 1;			// digit according to copy-length
}

/*
 func: Set bn to 0
 Note: sign set to 1
*/
void BN_zero(pBIGINT bn)
{
	int i = 0;

	bn->sign = 1;
	bn->digit = 0;
	for(;i < MAX_LEN; i++){
		bn->num[i] = 0;
	}
}

/*
 func: copy bn2 values[p1, p2] to bn1
		[bn1: 4,6,2,3	bn2: 8,5,9,0,1,4,2,2]
		BNcpy(bn1, bn2, 3, 6) ------> bn1: 0,1,4,2
 Note: Difference from BNjoint(): 
		1. Joint from the tail of bn1
		2. Copy from the head of bn1
*/
void BNcpy(pBIGINT bn1, pBIGINT bn2, int p1, int p2)
{
	BN_zero(bn1);
	BNjoint(bn1, bn2, p1, p2);
}


/*
 function: check the str is valid for Big Number
 return: valid ---> 1
		invalid---> 0
*/
int Check_Valid(char str[])
{
	char *ptr = str;

	if(*ptr == '-' || *ptr == '+')		// check the sign
		ptr++;
	while(*ptr != '\0'){
#if TEST_BN
		printf("%c ", *ptr);
#endif
		if(!isdigit((int)*ptr))
			return 0;
		ptr++;
	}
#if TEST_BN
	printf("\n");
#endif
	return 1;
}

/*
 function: Big Number in '%c' ---> Big Number in '%d'.
 Note:	BN in Array should be reversed !!! 
		It is convenient for caculation.
*/
void Str_To_BigNum(char str[], pBIGINT bn)
{
	int i = 0, j = 0;
	char bkup[MAX_LEN] = {0};
	char *p;

	if(!Check_Valid(str)){
		printf("This string is invalid for Big Number!\n");
		return;
	}

	BN_zero(bn);

	p = str;
	if(*p == '-'){				// get sign
		bn->sign = -1;
		p++;
	}else{
		bn->sign = 1;
		if(*p == '+')
			p++;
	}
	while(*p == '0') p++;		// skip leading 0

	while(*p != '\0'){
		bkup[i++] = *p - '0';
		p++;
	}
	bn->digit = i;
	/* reverse the array */
	for(; j < bn->digit; j++){
		bn->num[j] = bkup[--i];
	}
}


/*------------------------------------------------------------------*/
/*
Refer to URL:
https://blog.csdn.net/qq_36894136/article/details/79074728
*/
/*------------------------------------------------------------------*/

/*
 func: result = BNa + BNb
 Note: carry influence digit
*/
void BigIntAdd(pBIGINT BNa, pBIGINT BNb, pBIGINT BNc)
{
	int i = 0, carry = 0;			// carry for adding.
	struct bigint Result = {"temp", {0}, 0, 0};
	pBIGINT tlag, tsht, result = &Result;		// t_larger, t_shorter

	result->sign = BNa->sign;					// sign align at BNa
	/* select larger digit, copy its values to result */
	if(BNa->digit > BNb->digit){
		tlag = BNa; tsht = BNb;
	}else{
		tlag = BNb; tsht = BNa;
	}
	BNcpy(result, tlag, 0, tlag->digit-1);

	/* start addition */
	for(i = 0; i < tlag->digit; i++){
		result->num[i] = result->num[i] + tsht->num[i] + carry;
		carry = result->num[i] / 10;			// get carry
		result->num[i] = result->num[i] % 10;	// reserve one digit
	}
	if(carry){						// In case the highest bit has carry
		result->num[i++] += carry;
		result->digit++;
	}
	BNcpy(BNc, result, 0, result->digit-1);
} 

/*
 func: result = BNa - BNb
 Note: borrow influence digit
*/
void BigIntSub(pBIGINT BNa, pBIGINT BNb, pBIGINT BNc)
{
	int i = 0, cmp = 0, borrow = 0;
	struct bigint Result = {"temp", {0}, 0, 0};
	pBIGINT minuend, subend, result = &Result;		// minuend - subtrahend

	cmp = BigIntCompare(BNa, BNb);
	if(abs(cmp) == 2 || abs(cmp) == 6){		// only compare absolute value
		minuend = BNa; subend = BNb;
		result->sign = minuend->sign;
	}else{
		minuend = BNb; subend = BNa;
		result->sign = minuend->sign;
	}

	// copy BNa to result
	BNcpy(result, minuend, 0, minuend->digit-1);

	for(i = 0; i <= subend->digit; i++){
		result->num[i] = result->num[i] - subend->num[i] - borrow;
		if(result->num[i] < 0){				// if negative
			result->num[i] += 10;			// borrow from higher bit
			borrow=1;
		}else
			borrow=0;
	}

	if(borrow==1)
		result->num[i]=result->num[i]-borrow;
	// check if the highest bits are 0, modify values
	i = minuend->digit;
	while(i > 0){
		if(result->num[i] == 0)
			i--;
		else
			break;
	}
	result->digit = i+1;

	BNcpy(BNc, result, 0, result->digit-1);
}

/*
 func: result = BNa * BNb
 Note: set result to 0 brefore multiply
*/
void BigIntMul(pBIGINT BNa, pBIGINT BNb, pBIGINT BNc)
{
	char carry, temp;
	int i, j, pos;
	struct bigint Result = {"temp", {0}, 0, 0};
	pBIGINT result = &Result;

	/* multiply each digit of the multiplier(n2) times multiplicand(n1) */
	for(i = 0; i < BNb->digit; i++){
		carry = 0;
		for(j = 0; j < BNa->digit; j++){
			temp = BNb->num[i] * BNa->num[j] + carry;
			carry = temp/10;							// deal following add
			temp = temp%10;
			pos = i + j;
			/* put temp values to result */
			result->num[pos] += temp;					// key step
			carry += result->num[pos]/10;		// get carry(not always 1)
			result->num[pos] %= 10;
		}
		if(carry > 0){
			result->num[i+j] = carry;
			result->digit = i+j+1;
		}else
			result->digit = i+j;
	} 
	result->sign = BNa->sign * BNb->sign;			// sgin

	BNcpy(BNc, result, 0, result->digit-1);
}

/*
 Func: BNa / BNb = result ...... residue
 Note: 
*/
void BigIntDiv(pBIGINT BNa, pBIGINT BNb, pBIGINT BNc, pBIGINT residue)
{
	int i = 0, j = 0, k = 0, m = 0, cmp;	// k--> value, m-->bit-num. Both for quotient
	char t;
	char num[8] = {0};
	struct bigint Result = {"result", {0}, 0, 0}, Temp = {"temp", {0}, 0, 0}, KIT = {"k", {0}, 0, 0};
	pBIGINT result = &Result, tmp = &Temp, K = &KIT;

	result->sign = BNa->sign * BNb->sign;		//symbol of quotient

	m = BNa->digit - BNb->digit + 1;
	i = m;
	result->digit = m;
	BNcpy(tmp, BNa, i, BNa->digit-1);		// Length of minuend.
	while(i-- >= 0){
		BN_zero(K);
		BN_zero(residue);
		for(j = 0; j < 10; j++){
			sprintf(num, "%d", j);
			Str_To_BigNum(num, K);
			BigIntMul(K, BNb, K);
			BigIntSub(tmp, K, residue);

			if(BigIntCompare(residue, BNb) == 1){
				result->num[i+1] = j;
#if TEST_BN
				printf("\033[40;36mresult[%d]=%d\033[0m\n", i+1, result->num[i+1]);
#endif
				break;
			}
		}
		BNcpy(tmp, BNa, i, i);
		BNjoint(tmp, residue, 0, residue->digit-1);
	}

	/* check whether the head of result=0 */
	for(i = m-1; i > 0; i--){
		if(result->num[i] == 0)
			result->digit--;
	}

	BNcpy(BNc, result, 0, result->digit-1);
}

/*
 Func: calculate according to METHOD and sign.
 Note:  1. recognize negative calculation in '+' and '-'.
		2. deal with uncertain parameters.
*/
void Calculate_Big_Numer(enum METHOD way, ...)
{
	int comp = 0;
	va_list args;
	pBIGINT BNa, BNb, BNc, BNd;

	/* A good sample of va_list in uncertain parameters */
	va_start(args, way);									// start
	BNa = va_arg(args, pBIGINT);
	BNb = va_arg(args, pBIGINT);

	comp  = BigIntCompare(BNa, BNb);
#if TEST_BN
	printf("\033[40;33mreturn compare:%d\033[0m\n", comp);
#endif

	switch(way){
		case ADD:												// Addition
			BNc = va_arg(args, pBIGINT);
			printf("\033[40;36mAdd: bn1 + bn2 = bn3\033[0m\n");
			if(abs(comp) < 3)					// the same sign
				BigIntAdd(BNa, BNb, BNc);
			else
				BigIntSub(BNa, BNb, BNc);
			strcpy(BNc->name, "BN_add");
			BN_print(BNc);
			break;
		case SUB:												// Subtraction
			BNc = va_arg(args, pBIGINT);
			printf("\033[40;36mSub: bn1 - bn2 = bn3\033[0m\n");
			if(abs(comp) < 3)					// the same sign
				BigIntSub(BNa, BNb, BNc);
			else
				BigIntAdd(BNa, BNb, BNc);
			strcpy(BNc->name, "BN_subtract");
			BN_print(BNc);
			break;
		case MUL:												// Multiplication
			BNc = va_arg(args, pBIGINT);
			printf("\033[40;36mMultiply: bn1 * bn2 = bn3\033[0m\n");
			BigIntMul(BNa, BNb, BNc);
			strcpy(BNc->name, "BN_multiply");
			BN_print(BNc);
			break;
		case DIV:												// Division
			BNc = va_arg(args, pBIGINT);
			BNd = va_arg(args, pBIGINT);
			printf("\033[40;36mDivise: bn1 / bn2 = bn3 ... bn4\033[0m\n");
			if(BNb->digit == 0){
				printf("Divisor cannot be 0!!!\n");
				break;
			}
			BigIntDiv(BNa, BNb, BNc, BNd);
			strcpy(BNc->name, "BN_divise");
			BN_print(BNc);
			BN_print(BNd);
			break;
		case FAC:												// Factorial

			break;
		case SQRT:												// Square Root

			break;
		default:
			break;
	}
	va_end(args);											// end
}

int main()
{
	int i = 0;
	char str[MAX_LEN] = {0};
	struct bigint BigNumA = {"BN_A", {0}, 0, 0}, BigNumB = {"BN_B", {0}, 0, 0}, BigNumC = {"BN_result", {0}, 0, 0}, BigNumD = {"BN_residue", {0}, 0, 0};
	pBIGINT BNa = &BigNumA, BNb = &BigNumB, BNc = &BigNumC, BNd = &BigNumD;

	// Method to get BigNum
	strcpy(str, "00019435347589347593453");
	Str_To_BigNum(str, BNa);
	BN_print(BNa);
	strcpy(str, "000394356123");
	Str_To_BigNum(str, BNb);
	BN_print(BNb);

	Calculate_Big_Numer(ADD, BNa, BNb, BNc);
	Calculate_Big_Numer(SUB, BNa, BNb, BNc);
	Calculate_Big_Numer(MUL, BNa, BNb, BNc);
	Calculate_Big_Numer(DIV, BNa, BNb, BNc, BNd);

}

