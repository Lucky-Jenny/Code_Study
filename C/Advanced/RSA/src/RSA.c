#include "config.h"

static struct bigint BNA = {"A", {0}, 0, 0};
static struct bigint BNB = {"B", {0}, 0, 0};
static struct bigint BNC = {"C", {0}, 0, 0};

static pBIGINT BNa = &BNA, BNb = &BNB, BNc = &BNC;

/* No use at present */
void print_on_Test(char *format, ...)
{
	va_list parm;
	va_start(parm, format);
	printf(format, parm);
	va_end(parm);
}

void PrintKey(struct pPairkey *pkey)
{
	printf("\033[40;36mRSA Key:\n"
		"Public  Key(e,n): (%d, %d)\n"
		"Private Key(d,n): (%d, %d)\033[0m\n", pkey->e, pkey->n, pkey->d, pkey->n);
}

/*
// No use for now
bool IsNumber(const char *strNumber)
{
	unsigned int i;
	if(!strNumber)
		return false;
	for (i = 0; i < strlen(strNumber); i++){
		if (strNumber[i] < '0' || strNumber[i] > '9')
			return false;
	}
	return true;
}
*/

int Char_To_Int(char x[])
{
	int i = 0, j = 1, tmp = 0;

#if TEST_RSA
	printf("ptr:%s, strlen(ptr)=%d\n", x, (int)strlen(x));
#endif
	for(i = strlen(x)-1; i >= 0; i--){
		tmp += (x[i] - '0')*j;
		j *= 10;
	}
	return tmp;
}

/*
 Func: Judge whether num is prime
 Note: try number from 2 to sqrt(num)
*/
bool IsPrimeNumber(unsigned int num)
{
	unsigned int i, sqr;
	if( num <= 1 )
		return false;
	sqr = (unsigned int)sqrt((double)num);
	for( i = 2; i <= sqr; i++ ){
		if( (num % i) == 0 ){
#if TEST_RSA
			printf("%d %% %d =0\n", num, i);
#endif
			return false;
		}
	}
	return true;
}

/*
 Func: Judge P, Q coprime.
 Note:  1. P(Q) prime; P(Q) >= 2; P != Q
 		2. Detect whether there is common divisor.
*/
bool CoPrime(unsigned int P, unsigned int Q)
{
	unsigned int i = 0, temp = 0;
	bool Flag = true, pFlag = true, qFlag = true;

	if(P<2 || Q<2)
		return false;

	if(!IsPrimeNumber(P)){
		printf("P is Invalid! P should be 1-%d Integers!\n", MAX_E_D);
		return false;
	}
	if(!IsPrimeNumber(Q)){
		printf("Q is Invalid! Q should be 1-%d Integers!\n", MAX_E_D);
		return false;
	}
	if(P == Q){
		printf("P=Q! Unsafe for Encryption, please re-input!\n" );
		return false;
	}

	temp = (P > Q) ? Q : P;
	for(i=2; i<=temp && Flag; i++){
		if(P % i == 0)
			pFlag = false;
		if(Q % i == 0)
			qFlag = false;
		if(!pFlag && !qFlag)
			Flag = false;
	}
	if(Flag)
		return true;
	else
		return false;
}

/*
 Func: Lowest Common Multiple
 Note: start with the larger number.
*/
unsigned int LCM(unsigned int a, unsigned int b)
{
	unsigned int i = 0, temp = 0, lcm = 0;
	
	if(a > b)
		temp = a;
	else
		temp = b;
	for(i = temp; i > 0; i++){
		if((i%a == 0) && (i%b == 0))
			break;
	}
	lcm = i;
	return lcm;
}

/*
 Func: Greatest Common Divisor
 Note: Recursive Function
*/
unsigned int GCD(unsigned int a, unsigned int b)
{
	return b==0 ? a : GCD(b, a%b);		// beautiful
}

/*
 Func: Generate pair Key, private and public
 Note: 1.Check p, q before generating pair key.
 	   2.Add return to judge D,E,N is good enough
 	    -If D,E is too large, Decryption will cost much time!!!
 	    -Try fix this problem later.
*/
int MakePairkey(unsigned int uiP, unsigned int uiQ, struct pPairkey *pkey)
{
	unsigned int N = 0, L = 0, E = 1, D = 1;

	/* Firstly, judge P and Q meet the requirement.*/
	if(!CoPrime(uiP, uiQ))
		return 0;
	printf("Generating Private Key...\n");

	/* Start to generate Pair Key*/
	N = uiP *uiQ;
	L = LCM(uiP-1, uiQ-1);
	while(++E < L){
		if(GCD(E, L) == 1)
			break;
	}
	while(++D < L){
		if((D*E)%L == 1)
			break;
	}

	/* D,E should not be too big, N >=3 */
	if(Int_Length(D) > MAX_E_D || Int_Length(E) > MAX_E_D || Int_Length(N) < 3){
		printf("Abort!! D or E or N not satisfied!!\n");
		return 0;
	}

	pkey->d = D;
	pkey->e = E;
	pkey->n = N;

	return 1;
}

/*
 Func: Save RSA Key into specified file.
 Note:
*/
void SaveKey(const char *strFile, struct pPairkey *pkey)
{
	int i = 0;
	char cmd_rm[64] = {0};
	FILE *fp = NULL;

	/* remove related files before creating RSA key. */
	sprintf(cmd_rm, "rm -f %s %s %s", KEY_FILE, ENCRYPT_FILE, DECRYPT_FILE);
	system(cmd_rm);

	fp = fopen(strFile, "w+");
	fprintf(fp, "D:%d\nE:%d\nN:%d\n", pkey->d, pkey->e, pkey->n);
	fclose(fp);
}

/*
 Func: Get RSA Key from specified file.
 Note: If get failed, return 0.
*/
int GetKey(const char *strFile, struct pPairkey *pkey)
{
	FILE *fp = NULL;
	char *ptr = NULL;
	char tmp[32] = {0};

	if((fp = fopen(strFile, "r")) == NULL){
		perror("Failed to open the file!");
		return 0;
	}
	while(fgets(tmp, sizeof(tmp), fp)){
		ptr = strtok(tmp, ":");				/* cut the first string */
		if(*ptr == 'D'){
			ptr = strtok(NULL, "\n");		/* important!!!! */
			pkey->d = Char_To_Int(ptr);
		}
		else if(*ptr == 'E'){
			ptr = strtok(NULL, "\n");
			pkey->e = Char_To_Int(ptr);
		}
		else if(*ptr == 'N'){
			ptr = strtok(NULL, "\n");
			pkey->n = Char_To_Int(ptr);
		}
	}
	return 1;
}

/*
 Func: Int_Length
 Return: the bit length of integer
*/
int Int_Length(int n)
{
	if(n == 0)
		return 0;
	else
		return Int_Length(n/10) + 1;
}

/*
 Func: Give Offset to char
 Note: ASC_OFFSET is Macro, which can be defined by user
*/
int Offset_Char(char alpha, int flag)		// flag=1: set; flag=0: reset
{
	if(flag)
		return (alpha + ASC_OFFSET);
	else
		return (alpha - ASC_OFFSET);
}

/*
 Func: RSA Encryption
 Note: 1.turn every word to "xxx" (the length is due to the length of N)
	   3.RSA calculation requires BigNumber.
*/
void RSA_Encrypt(struct pPairkey *pkey, char *buff, char *cipher)
{
	int i=0, temp=0, tst_tmp=0, len=0, mlength=0, gap=0;
	char str[32];

	len = Int_Length(pkey->n);
	mlength = strlen(buff);
	for(i=0; i <= mlength; i++){
		if(i == mlength){			// put the length at end of plaintext.
			sprintf(str, "%d", len);
			strcat(cipher, str);
			break;
		}
		
		temp = Offset_Char(buff[i], 1);
#if TEST_RSA		
		printf("text[%d]:%d+%d = %d\n", i, buff[i], ASC_OFFSET, temp);
#endif
		/* temp = (word^E)/N */
		Int_To_BigNum(temp, BNa);
		Int_To_BigNum(pkey->e, BNb);
		Calculate_Big_Numer(POW, BNa, BNb, BNc);

		Int_To_BigNum(pkey->n, BNb);
		Calculate_Big_Numer(MOD, BNc, BNb, BNa);

		temp = BigNum_To_Int(BNa);

		/* Test whether the cipher can be returned. */
#if TEST_RSA
		printf("Turn:   %d\n", temp);
		Int_To_BigNum(temp, BNa);
		Int_To_BigNum(pkey->d, BNb);
		Calculate_Big_Numer(POW, BNa, BNb, BNc);

		Int_To_BigNum(pkey->n, BNb);
		Calculate_Big_Numer(MOD, BNc, BNb, BNa);

		tst_tmp = BigNum_To_Int(BNa);

		printf("Return: %d\n", tst_tmp);
#endif

		/* align the length with N, by adding '0'. */
		if(temp == 0)
			gap = len - 1;
		else
			gap = len - Int_Length(temp);
		if(gap > 0){
			while(--gap >= 0){
				strcat(cipher, "0");
			}
		}
		sprintf(str, "%d", temp);
		strcat(cipher, str);
#if TEST_RSA
		printf("plaintext:%s\n", cipher);
#endif
	}
}

/*
 Func: RSA_Decrypt
 Note: 1.Get the length from the last bit.
 	   2.Remind Offset return
*/
void RSA_Decrypt(struct pPairkey *pkey, char *cipher, char *plaintext)
{
	int i = 0, j = 0, temInt = 0, intlen = 0, de_time = 0;
	char str[32];
	char *p, *q;

	/* get the length of each number from the end. */
	p = cipher;
	for(; *(p+1) != '\0'; p++);
	intlen = *p - '0';
	
	/* calculate the length of plaintext(loop time) */
	de_time = (strlen(cipher)-1)/intlen;
#if TEST_RSA
	printf("word_len=%d  loop time=%d\n", intlen, de_time);
#endif

	p = cipher;

	for(; i < de_time; i++){
		q = p;
		temInt = 0;
		for(j = 0; j < intlen; j++){		// constant length
			temInt = temInt*10 + *q-'0';
			q++;
		}

		/* text = (cipher^D)/N */
		Int_To_BigNum(temInt, BNa);
		Int_To_BigNum(pkey->d, BNb);
		Calculate_Big_Numer(POW, BNa, BNb, BNc);

		Int_To_BigNum(pkey->n, BNb);
		Calculate_Big_Numer(MOD, BNc, BNb, BNa);

		temInt = BigNum_To_Int(BNa);

		printf("%c", Offset_Char(temInt, 0));
		sprintf(str, "%c", Offset_Char(temInt, 0));
		strcat(plaintext, str);
	
		p = p + intlen;
#if TEST_RSA
		printf("RSA get=%d, after_offset:%d(why?)--->%s\ntext:%s\n", temInt, Offset_Char(temInt, 0), str, plaintext);
#endif
	}
	printf("\n");
}

/*
 Func: Read context from file to buff
*/
void FileIn(const char *strFile, char inBuff[])
{
	FILE *fp = NULL;
	char Buff[MAX_FILE] = {0}, temp[1024] = {0};

	if((fp = fopen(strFile, "r")) == NULL){
		perror("Failed to open the file!");
		return;
	}
	while(fgets(temp, sizeof(temp), fp)){
		strcat(Buff,temp);
	}
	fclose(fp);
	strcpy(inBuff, Buff);
#if TEST_RSA
	printf("---FileIn()---\n");
	printf("Buff:\n%s\n", inBuff);
	printf("--------------\n");
#endif
}

/*
 Func: Print context to file
*/
void FileOut(char *strOut, const char *strFile)
{
	FILE *fp = NULL;

	fp = fopen(strFile, "w+");
	fprintf(fp, "%s", strOut);
	fclose(fp);
}


