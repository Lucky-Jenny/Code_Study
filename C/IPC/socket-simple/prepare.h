#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Socket */
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 1500			// Target Port
#define IP "127.0.0.1"		// Target IP [Local]
#define MAX_DATA 1024			// Max length of data
/* Server */
#define BACKLOG 5

#define TEST 0			// for test to print log of process
#define SHOW_DES 0

// If u want to use a function in more resource files, u should define it in ".c" and declare it in ".h".
extern void Print_DES(char format[], char *tmp);

/****    DES    ****/
extern char *Des_Encrypt(char str[]);
extern char *Des_Decrypt(char hex[]);

