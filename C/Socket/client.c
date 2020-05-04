#include "prepare.h"

int main()
{
	int sockfd,new_fd;			// Socket Handle
	struct sockaddr_in dest_addr;	// Target Address Info
	char buf[MAX_DATA];			// storage of received data
	char *q = NULL;
	int try = 0;

	sockfd=socket(AF_INET,SOCK_STREAM,0);	// Set up Socket
	if(sockfd==-1){
		printf("socket failed:%d\n",errno);
	}
    // Refer to 'server.c', you can acquire the meaning of values.
	dest_addr.sin_family=AF_INET;
	dest_addr.sin_port=htons(PORT);
	dest_addr.sin_addr.s_addr=inet_addr(IP);
	bzero(&(dest_addr.sin_zero),8);
	
	printf("Client: send conection socket and receive message from server.\n-------\n");
	while(try++ < 5){
		if(connect(sockfd,(struct sockaddr*)&dest_addr,sizeof(struct sockaddr))==-1){
			printf("connect failed:%d\n",errno);
		}
		else{
			printf("Connect success!\n");
			while(1){
				if(recv(sockfd,buf,MAX_DATA,0) == 0){
					break;
				}
				if(buf){
#if SHOW_DES
					printf("Get code:\033[40;33m%s\033[0m\n", buf);
#endif
					q = Des_Decrypt(buf);
					printf("Received:\033[40;36m%s\033[0m\n", q);
				}
				memset(buf, 0, sizeof(buf));
				sleep(1);
			}
		}
		sleep(2);
	}
	close(sockfd);		// close socket
	return 0;
}
