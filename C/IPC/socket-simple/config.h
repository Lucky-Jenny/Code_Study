#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
/* Socket */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 1500			// Target Port
#define IP "127.0.0.1"		// Target IP [Local]
#define MAX_DATA 1024		// Max length of data
/* Server */
#define BACKLOG 5
/* Enable DES */
#define USE_DES 1

/* Test */
#define TEST 0			// for test to print log of process


extern int sin_size;

/* 
 [Note] define function in ".c"
		declare function in ".h"
*/
extern void Print_DES(char format[], char *tmp);

/****    DES    ****/
extern char *Des_Encrypt(char str[]);
extern char *Des_Decrypt(char hex[]);

/****  socket   ****/
extern int connect_socket(char *target_ip, int port);
extern int listen_socket(char *ip, int port, char *interface); 

