#include "DES.h"
#include "../prepare.h"


char *Des_Encrypt(char str[])
{
	int i = 0, j = 0, len = 0, k = 0;
	char *p, *q;
	char hex[32] = {0}, tmp[16] = {0};
	
	len = strlen(str);
	run_time = len/8 + 1;
#if TEST
	printf("len=%d run_time=%d\n", len, run_time);
	int m = 0;
	for(m=0; m<len; m++){
		printf("%c ", str[m]);
	}
#endif
	SetKey(KEY);
	memset(Code_hex, 0, sizeof(Code_hex));	// For Socket communication in loop
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
	int i = 0, j = 0, len = 0, k = 0;
	char *p, *q;
	char getstr[8] = {0};
	char tmp[32] = {0};

	len = strlen(hex);
	run_time = len/16;			// hex_code --> 16*n
#if TEST
	printf("run_time=%d\tlength=%d\n", run_time, len);
#endif
	SetKey(KEY);
	q = hex;
	memset(Message, 0, sizeof(Message));	// For Socket
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
		strcat(Message, getstr);
		memset(tmp, 0, sizeof(tmp));
		i++;
	}
	p = Message;
	return p;
}

/*
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
*/
