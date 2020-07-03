#include "config.h"

void Usage()
{
	printf(" Usage: rsa -e File (Encryption)\n"
			"        rsa -d File (Decryption)\n"
			"        rsa -k (Key generate)\n");
}

/*
 name:		CheckParse
 function:	check patameters of the application
 return:	Valid--> true; Invalid-->false
*/
bool CheckParse(int argc, char **argv)
{
	bool bRes = false;

	if(argc == 1 || argc > 3)
		Usage();
	else{
		if(argv[1][1] == 'e' || argv[1][1] == 'd' || argv[1][1] == 'k')
			bRes = true;
		else
			Usage();
	}
	return bRes;
}

int main(int argc, char **argv)
{
	struct pPairkey pkey;
	unsigned int p = 0, q = 0;
	char FileName[32];
	char Code[RSA_LEN];
	char Buffer[RSA_LEN];

	if(!CheckParse(argc, argv))
		return 0;

	if(argv[1][1] == 'k'){
		while(!MakePairkey(p, q, &pkey)){
			p = q = 0;
			p = Find_Prime_Num();
			q = Find_Prime_Num();
		}
		printf("P=%d, Q=%d\n", p, q);
		PrintKey(&pkey);
		SaveKey(KEY_FILE, &pkey);
		return 0;
	}

	strcpy(FileName, argv[2]);
	if(access(FileName, F_OK) != 0){	// file exist?
		printf("No such file!\n");
		return 0;
	}
	if(!GetKey(KEY_FILE, &pkey))		// file can be read?
		return 0;

	PrintKey(&pkey);

	if(argv[1][1] == 'e'){
		FileIn(FileName, Buffer);
		RSA_Encrypt(&pkey, Buffer, Code);
		FileOut(Code, ENCRYPT_FILE);
		printf("\033[40;33mEncryption Complete! Codes saved in %s\033[0m\n", ENCRYPT_FILE);
	}
	else if(argv[1][1] == 'd'){
		FileIn(FileName, Code);
		RSA_Decrypt(&pkey, Code, Buffer);
		FileOut(Buffer, DECRYPT_FILE);
		printf("\033[40;33mDecryption Complete! Text saved in %s\033[0m\n", DECRYPT_FILE);
	}
	return 0;

}
