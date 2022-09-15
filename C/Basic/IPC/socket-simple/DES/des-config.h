#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* DES */
#define STR_LEN 128
#define HEX_LEN 512

/* TEST */
#define TEST_DES 0

/* static values in DES */
static char KEY[] = "whatareu";
static char Code_hex[HEX_LEN] = {0};
static char Message[STR_LEN] = {0};
static int run_time = 0;


/* DES API */
extern void SetKey(char My_key[8]);
extern void Run_Des(char My_message[],char HexMssage[]);
extern void Run_desDes(char My_message[],char HexMessage[]);


