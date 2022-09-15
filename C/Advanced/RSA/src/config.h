#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>

/* File */
#define DECRYPT_FILE "decrypt.txt"
#define ENCRYPT_FILE "encrypt.txt"
#define KEY_FILE "Key_RSA.txt"
#define MAX_FILE 1024*1024*2

/* Offset of char in ASCII */
#define ASC_OFFSET 35

/* Length of Numbers */
#define PRIME_LEN 2			// better <= 3, or cost much time
#define BN_LEN 1024*100
#define RSA_LEN 63001
#define MAX_E_D 4			// Max length of D,E

/* For Test */
#define TEST 1
#define TEST_RSA 0
#define TEST_BN 0
#define TEST_PRIME 0


typedef enum
{
	false = 0,
	true  = 1
}bool;


/* struct of Big Number */
typedef struct bigint{
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


// Pair of Private and Public Key
static struct pPairkey{
	unsigned int d;
	unsigned int e;
	unsigned int n;
}pairkey;


/*************** RSA ***************/
extern void PrintKey(struct pPairkey *pkey);
extern int Char_To_Int(char x[]);
extern bool IsPrimeNumber(unsigned int num);
extern bool CoPrime(unsigned int P, unsigned int Q);
extern unsigned int LCM(unsigned int a, unsigned int b);
extern unsigned int GCD(unsigned int a, unsigned int b);
extern int MakePairkey(unsigned int uiP, unsigned int uiQ, struct pPairkey *pkey);
extern void SaveKey(const char *strFile, struct pPairkey *pkey);
extern int GetKey(const char *strFile, struct pPairkey *pkey);
extern int Int_Length(int n);
extern int Offset_Char(char alpha, int flag);
extern void RSA_Encrypt(struct pPairkey *pkey, char *buff, char *cipher);
extern void RSA_Decrypt(struct pPairkey *pkey, char *cipher, char *plaintext);
extern void FileIn(const char *strFile, char inBuff[]);
extern void FileOut(char *strOut, const char *strFile);

/*************** Big Number ***************/
extern void BN_print(pBIGINT bn);
extern int BigIntCompare(pBIGINT n1, pBIGINT n2);
extern int BNjoint(pBIGINT bn1, pBIGINT bn2, int p1, int p2);
extern void BN_zero(pBIGINT bn);
extern void BNcpy(pBIGINT bn1, pBIGINT bn2, int p1, int p2);
extern void Str_To_BigNum(char str[], pBIGINT bn);
extern void Int_To_BigNum(int x, pBIGINT bn);
extern char *BigNum_To_Str(pBIGINT bn);
extern int BigNum_To_Int(pBIGINT bn);
extern void Calculate_Big_Numer(enum METHOD way, ...);


/*************** Prime Number ***************/
extern unsigned int Find_Prime_Num();


