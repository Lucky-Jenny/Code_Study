#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define BN_LEN 10240
#define TEST_BN 0

typedef struct  bigint{
	char name[32];
	char num[BN_LEN];			// save in 'char', show in 'int'
	int sign;					// symbol: 1-->positive; -1-->negative
	int digit;					// length of this BN
}*pBIGINT;

enum METHOD{
	ADD,		// Addition
	SUB,		// Subtraction
	MUL,		// Multiplication
	DIV,		// Division -----> Quotient + Module
	QUO,		// Quotient
	MOD,		// Modulus
	FAC,		// Factorial
	POW,		// Power
};

/*
 Func: Print all values of struct bigint
 Note: Color the name of BN.
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
 Func: Compare n1 with n2
 return:  n1 = n2 ---> 0
 both >0, n1 > n2 ---> 2 (both < 0, |n1| > |n2| ---> -2)
 both >0, n1 < n2 ---> 1 (both < 0, |n1| < |n2| ---> -1)
 n1>0 n2<0, |n1| > |n2| --->  6	    |n1| < |n2| --->  3
 n1<0 n2>0, |n1| > |n2| ---> -6	    |n1| < |n2| ---> -3
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
 Func: BNx - 1
 Note: 1000 ---> 999
*/
void BN_degrese(pBIGINT BNx)
{
	int i = 1;

	if(BNx->num[0]){
		BNx->num[0]--;
		return;
	}else
		BNx->num[0] = 9;

	for(i = 1; i < BNx->digit; i++){
		if(BNx->num[i] == 0)
			BNx->num[i] = 9;
		else{
			BNx->num[i]--;
			break;
		}
	}
	/* Check whether head bit is 0 */
	if(BNx->num[BNx->digit-1] == 0)
		BNx->digit--;
}

/*
 Func: joint bn2 values(p1, p2) tothe tail of bn1
		[bn1: 4,6,2,3	bn2: 8,5,9,0,1,4,2,2]
		BNjoint(bn1, bn2, 3, 6) ------> bn1: 4,6,2,3,0,1,4,2
 Note: Exclude name and sign
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
 Func: Set bn to 0
 Note: sign = 1, digit = 1
*/
void BN_zero(pBIGINT bn)
{
	int i = 0;

	bn->sign = 1;
	bn->digit = 1;
	for(;i < BN_LEN; i++){
		bn->num[i] = 0;
	}
}

/*
 Func: Judge whether BN is zero.
 Note:  BN == 0 ---> 1
		BN != 0 ---> 0
	[Correct digit=1 when BN=0]
*/
int Is_BN_zero(pBIGINT bn)
{
	int i = 0;

	for(; i < bn->digit; i++){
		if(bn->num[i] != 0)
			return 0;
	}
	bn->digit = 1;
	return 1;
}

/*
 Func: Copy bn2 values[p1, p2] to bn1
		[bn1: 4,6,2,3	bn2: 8,5,9,0,1,4,2,2]
		BNcpy(bn1, bn2, 3, 6) ------> bn1: 0,1,4,2
 Note: Difference from BNjoint
		1. Joint---> start from the tail of bn1
		2. Copy ---> start from the head of bn1
*/
void BNcpy(pBIGINT bn1, pBIGINT bn2, int p1, int p2)
{
	BN_zero(bn1);
	bn1->digit = 0;					// Fix: correct the right position of joint.
	BNjoint(bn1, bn2, p1, p2);
}


/*
 Func: Check whether the string is valid for Big Number
 return: valid ---> 1
		invalid---> 0
*/
int Check_Valid(char str[])
{
	char *ptr = str;

	if(*ptr == '-' || *ptr == '+')		// check the sign
		ptr++;
	while(*ptr != '\0'){
		if(!isdigit((int)*ptr))
			return 0;
		ptr++;
	}
	return 1;
}

/*
 Func: String in '%c' ---> Big Number in '%d'.
 Note:
	1."000234"-->234; "-0546"-->-546
	2.BN in Array should be reversed !!! 
	3.XXX Cannot define function of 'pBIGINT'!!! XXX
	  Because pointer will change original address.
	4.Special handle when value = 0.
*/
void Str_To_BigNum(char str[], pBIGINT bn)
{
	int i = 0, j = 0;
	char bkup[BN_LEN] = {0};
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

	/*
	 fix Bug: "stack-buffer-underflow" reported in AddressSanitizer.
	 - The issue happen in reverse the array		-----> line = 246
	 - When value = 0, size = 1,
		loop still go. which cause bkup memory leaked.
	 - Therefore, return if detect value = 0.
	*/
	if(*p == '\0')
		return;

	while(*p != '\0'){
		bkup[i++] = *p - '0';
		p++;
	}

	if(i)
		bn->digit = i;
	else						// when BN = 0, digit = 1
		bn->digit = 1;
	
	/* reverse the array */
	for(j = 0; j < bn->digit; j++)
		bn->num[j] = bkup[--i];
}

/*
 Func: Put small integer into Big Number
 Note:	Only support for little number !!! 
		If too big, still require Str_To_BigNum()
*/
void Int_To_BigNum(int x, pBIGINT bn)
{
	char str[32];

	snprintf(str, sizeof(str), "%d", x);
	Str_To_BigNum(str, bn);
}

/*
 Func: Turn BN to char*
 Note: btter use snprintf(), more safety.
*/
char *BigNum_To_Str(pBIGINT bn)
{
	int i = 0;
	char tmp[4];
	char *bn_str = (char *)malloc(sizeof(char) * BN_LEN);

	for(i = bn->digit-1; i >= 0; i--){
		sprintf(tmp, "%d", bn->num[i]);
		strcat(bn_str, tmp);
	}
	return bn_str;
}

/*
 Func: Turn BN to int
 Note:  If put 'int' into param, it should be '*int', Or invalid!!
*/
int BigNum_To_Int(pBIGINT bn)
{
	int i = 0, bit = 1, tmp = 0, max = 8;

	if(bn->digit > max){
		printf("Can't turn to int! ---> Length of BN > %d\n", max);
		return 0;
	}
	for(; i < bn->digit; i++){
		tmp += bit * bn->num[i];
		bit *= 10;
	}
	return tmp;
}

/*------------------------------------------------------------------*/
/*
Refer to URL:
https://blog.csdn.net/qq_36894136/article/details/79074728
*/
/*------------------------------------------------------------------*/

/*
 Func: result = BNa + BNb
 Note: carry influence digit
	[A] = [A] + [B] 
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
 Func: result = BNa - BNb
 Note: borrow influence digit
		[A] = [A] - [B]
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
 Func: result = BNa * BNb
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
			carry = temp / 10;							// deal following add
			temp = temp % 10;
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

	if(Is_BN_zero(result))
		BN_zero(result);

	BNcpy(BNc, result, 0, result->digit-1);
}

/*
 Func: BNa / BNb = result ...... residue
 Note: 
	1) Require BN_joint() to link residue to one bit from BNb
	2) If residue=0, no joint and go on.
	3) For a clear view in test, require BN_To_Str() to get BN with on '\n'
*/
void BigIntDiv(pBIGINT BNa, pBIGINT BNb, pBIGINT BNc, pBIGINT residue)
{
	int i, j, m, a_sign, b_sign;	// m-->bit-num. Both for quotient
	char num[8] = {0};
	struct bigint Result = {"result", {0}, 0, 0}, Temp = {"temp", {0}, 0, 0}, KIT = {"k", {0}, 0, 0};
	pBIGINT result = &Result, tmp = &Temp, K = &KIT;

	result->sign = BNa->sign * BNb->sign;		//symbol of quotient
	result->digit = BNa->digit;

	/* Avoid error when BNa/BNb is negative */
	a_sign = BNa->sign;
	b_sign = BNb->sign;
	BNa->sign = BNb->sign = 1;

	i = m = BNa->digit - BNb->digit;
	BNcpy(tmp, BNa, i, BNa->digit-1);		// Length of minuend.
	while(i-- >= 0){
		BN_zero(K);
		for(j = 0; j < 10; j++){
			Int_To_BigNum(j, K);
			BigIntMul(K, BNb, K);
			BigIntSub(tmp, K, residue);
#if TEST_BN
	/* Cannot print in one line Because it will call parms at the same time. */
			printf("[%s]-", BigNum_To_Str(tmp));
			printf("[%s]=", BigNum_To_Str(K));
			printf("[%s]\n", BigNum_To_Str(residue));
#endif
			if(BigIntCompare(residue, BNb) == 1){
				result->num[i+1] = j;
#if TEST_BN
				printf("\033[40;36mresult[%d]=%d\033[0m\n", i+1, result->num[i+1]);
#endif
				break;
			}
		}
		BNcpy(tmp, BNa, i, i);
		if(!Is_BN_zero(residue))
			BNjoint(tmp, residue, 0, residue->digit-1);
	}
#if TEST_BN
	snprintf(result->name, sizeof(result->name), "BN_quotient_tmp");
	BN_print(result);
#endif
	/* Recovery sign */
	BNa->sign = a_sign;
	BNb->sign = b_sign;

	/* check and rm the head bits which result=0 */
	for(i = result->digit-1; i >= 0; i--){
		if(result->num[i] != 0)
			break;
		result->digit--;
	}
	BNcpy(BNc, result, 0, result->digit-1);
}

/*
 Func: BNc = BNa!
 Note:  No need to calculate degrese time.
		Just compare tmp with '1'.
*/
void BigIntFac(pBIGINT BNa, pBIGINT BNc)
{
	if(Is_BN_zero(BNa)){
		Int_To_BigNum(1, BNc);		// 0! = 1
		return;
	}
	struct bigint Temp = {"temp", {0}, 0, 0}, Unit = {"unit", {0}, 0, 0};
	pBIGINT tmp = &Temp, unit = &Unit;

	BNcpy(BNc, BNa, 0, BNa->digit-1);
	BNcpy(tmp, BNa, 0, BNa->digit-1);

	Int_To_BigNum(1, unit);
	while(BigIntCompare(tmp, unit) != 0){
		BN_degrese(tmp);
		BigIntMul(BNc, tmp, BNc);
	}
}

/*
 Func: BNc = BNa^(BNb)
 Note: Attention to BNc->sign
*/
void BigIntPower(pBIGINT BNa, pBIGINT BNb, pBIGINT BNc)
{
	struct bigint Temp = {"temp", {0}, 0, 0}, Unit = {"unit", {0}, 0, 0}, Judge = {"judge", {0}, 0, 0};
	pBIGINT tmp = &Temp, unit = &Unit, judge = &Judge;

	BNcpy(BNc, BNa, 0, BNa->digit-1);

	Int_To_BigNum(1, unit);
	while(BigIntCompare(BNb, unit) != 0){
		BN_degrese(BNb);
		BigIntMul(BNc, BNa, BNc);
	}

	/* Judge BNc sign by (BNb % 2) ?= 0 */
	Int_To_BigNum(2, unit);
	BigIntDiv(BNb, unit, tmp, judge);
#if TEST_BN
	printf("Judge BN_Power Sign: BNb %% 2 ?=0\n");
	BN_print(judge);
#endif
	if(judge->num[0] == 0)
		BNc->sign = 1;
	else
		BNc->sign = -1;
}

/*
 Func: calculate according to METHOD and sign.
 Note:
	1. recognize '+' and '-', chose the right calculation.
	2. use 'va_list' to deal with uncertain parameters.
	3. provide 'QUO' and 'MOD' to separate 'DIV'.
*/
void Calculate_Big_Numer(enum METHOD way, ...)
{
	int comp = 0;
	pBIGINT BNa, BNb, BNc, BNd;
	struct bigint Back = {"Back_up", {0}, 0};
	va_list args;
	

	/* A good sample of va_list in uncertain parameters */
	va_start(args, way);			// start
	BNa = va_arg(args, pBIGINT);
	BNb = va_arg(args, pBIGINT);

	comp  = BigIntCompare(BNa, BNb);
#if TEST_BN
	printf("\033[40;33mreturn compare:%d\033[0m\n", comp);
#endif

	switch(way){
		case ADD:										// Addition
			BNc = va_arg(args, pBIGINT);
			printf("\033[40;36mAdd: bn1 + bn2 = bn3\033[0m\n");
			if(abs(comp) < 3)				// the same sign
				BigIntAdd(BNa, BNb, BNc);
			else
				BigIntSub(BNa, BNb, BNc);
			snprintf(BNc->name, sizeof(BNc->name), "BN_Addition");
			BN_print(BNc);
			break;
		case SUB:										// Subtraction
			BNc = va_arg(args, pBIGINT);
			printf("\033[40;36mSub: bn1 - bn2 = bn3\033[0m\n");
			if(abs(comp) < 3)				// the same sign
				BigIntSub(BNa, BNb, BNc);
			else
				BigIntAdd(BNa, BNb, BNc);
			snprintf(BNc->name, sizeof(BNc->name), "BN_Subtract");
			BN_print(BNc);
			break;
		case MUL:										// Multiplication
			BNc = va_arg(args, pBIGINT);
			printf("\033[40;36mMultiply: bn1 * bn2 = bn3\033[0m\n");
			BigIntMul(BNa, BNb, BNc);
			snprintf(BNc->name, sizeof(BNc->name), "BN_Multiply");
			BN_print(BNc);
			break;
		case DIV:										// Division
			BNc = va_arg(args, pBIGINT);
			BNd = va_arg(args, pBIGINT);
			printf("\033[40;36mDivise: bn1 / bn2 = bn3 ... bn4\033[0m\n");
			if(Is_BN_zero(BNb)){
				printf("Divisor cannot be 0!!!\n");
				break;
			}
			BigIntDiv(BNa, BNb, BNc, BNd);
			snprintf(BNc->name, sizeof(BNc->name), "BN_quotient");
			snprintf(BNd->name, sizeof(BNd->name), "BN_residue");
			BN_print(BNc);
			BN_print(BNd);
			break;
		case QUO:										// Quotient
			BNc = va_arg(args, pBIGINT);
			BNd = &Back;
			printf("\033[40;36mQuotient: bn1 / bn2 = bn3\033[0m\n");
			if(Is_BN_zero(BNb)){
				printf("Divisor cannot be 0!!!\n");
				break;
			}
			BigIntDiv(BNa, BNb, BNc, BNd);
			snprintf(BNc->name, sizeof(BNc->name), "BN_Quotient");
			BN_print(BNc);
			break;
		case MOD:										// Modulus
			BNc = va_arg(args, pBIGINT);
			BNd = &Back;
			printf("\033[40;36mModulus: bn1 %% bn2 = bn3\033[0m\n");
			if(Is_BN_zero(BNb)){
				printf("Divisor cannot be 0!!!\n");
				break;
			}
			BigIntDiv(BNa, BNb, BNd, BNc);
			snprintf(BNc->name, sizeof(BNc->name), "BN_Modulus");
			BN_print(BNc);
			break;
		case FAC:										// Factorial
			if(BNa->sign == -1){
				printf("Factorial: Number can't be negative!!\n");
				return;
			}
			printf("\033[40;36mFactorial: bn1! = bn3\033[0m\n");
			snprintf(BNb->name, sizeof(BNc->name), "BN_factorial");
			BigIntFac(BNa, BNb);
			BN_print(BNb);
			break;
		case POW:										// Power
			if(BNb->sign == -1){
				printf("Power: The power number can't be negative!!\n");
				return;
			}
			BNc = va_arg(args, pBIGINT);
			printf("\033[40;36mPower: bn1^(bn2) = bn3\033[0m\n");
			snprintf(BNc->name, sizeof(BNc->name), "BN_Power");
			BigIntPower(BNa, BNb, BNc);
			BN_print(BNc);
			break;
		default:
			break;
	}
	va_end(args);					// end
}

int main()
{
	int i = 0;
	char str[BN_LEN] = {0};
	struct bigint BigNumA = {"BN_A", {0}, 0, 0};
	struct bigint BigNumB = {"BN_B", {0}, 0, 0};
	struct bigint BigNumC = {"BN_C", {0}, 0, 0};
	struct bigint BigNumD = {"BN_D", {0}, 0, 0};
	pBIGINT BNa = &BigNumA, BNb = &BigNumB, BNc = &BigNumC, BNd = &BigNumD;

	snprintf(str, sizeof(str), "000000000000");
	Str_To_BigNum(str, BNa);		// for Huge Number
	BN_print(BNa);

	Int_To_BigNum(5, BNb);		// for Small Number
	BN_print(BNb);

	//Calculate_Big_Numer(ADD, BNa, BNb, BNc);
	//Calculate_Big_Numer(SUB, BNa, BNb, BNc);
	//Calculate_Big_Numer(MUL, BNa, BNb, BNc);
	//Calculate_Big_Numer(DIV, BNa, BNb, BNc, BNd);
	//Calculate_Big_Numer(QUO, BNa, BNb, BNc);
	//Calculate_Big_Numer(MOD, BNa, BNb, BNc);
	Calculate_Big_Numer(FAC, BNa, BNc);
	Calculate_Big_Numer(POW, BNa, BNb, BNc);


}

