/*
-Author: Alex-dpx	Date: 2020/4/23
-Function:
 Encrypt string (of any length) by DES algorithm.
-Debug:
 Set 'TEST' 1. It can print the process and details.
*/

#include "des.h"

#define TEST 0

static char KEY[] = "whatareu";
static char Code_hex[HEX_LEN] = {0};
static char Message[STR_LEN] = {0};
static int run_time = 0;

char *Des_Encrypt(char str[])
{
	int i = 0, j = 0, len = 0, k = 0;
	char *p, *q;
	char hex[32] = {0}, tmp[16] = {0};
	
	len = strlen(str);
	run_time = len/8 + 1;
#if TEST
	printf("run_time=%d\tlength=%d\n", run_time, len);
	printf("str:%s\n", str);
#endif	
	SetKey(KEY);
	while(i < run_time){
		k = i*8;
		for(j=0; j<8; j++){
			tmp[j] = str[k+j];
#if TEST
			printf("str[%d]:%c\ttmp=%s\n", k+j, str[k+j], tmp);
		}
		printf("i=%d,tmp=%s\n", i, tmp);
#else
		}
#endif
		Run_Des(tmp, hex);			// Encryption
		strcat(Code_hex, hex);
		memset(tmp, 0, sizeof(tmp));
		i++;
	}
	p = Code_hex;
	return p;
}

char *Des_Decrypt(char hex[])
{
	int i = 0, j = 0, k = 0;
	char *p, *q;
	char getstr[8] = {0};
	char tmp[32] = {0};
	//SetKey(KEY);
	q = hex;
	while(i < run_time){
		k = i*16;
		for(j=0; j<16; j++){
			tmp[j] = hex[k+j];
#if TEST
			printf("str[%d]:%c\ttmp=%s\n", k+j, hex[k+j], tmp);
#endif
		}
		Run_desDes(getstr, tmp);	// Decryption
		getstr[8] = '\0';			// must, or it will get messy code.
#if TEST
		printf("getstr:%s\n", getstr);
#endif
		strcat(Message, getstr);
		memset(tmp, 0, sizeof(tmp));
		i++;
	}
	p = Message;
	return p;
}


int main()
{
	int i = 0;
	char My_message[STR_LEN] = {0};
	char *code, *result;
#if TEST
	strcpy(My_message, "what is your problem in this program?");
#else
	printf("Input what u want to encrypt:\n");
	scanf("%[^\n]", My_message);
#endif
	code = Des_Encrypt(My_message);
	printf("Encrypted Ciphertext:\n");
	printf("%s\n", code);
	printf("\n");

	result = Des_Decrypt(code);
	printf("The result of Decryption:\n");
	printf("%s\n", result);
	return 0;
}


