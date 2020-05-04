#include "prepare.h"

int main()
{
	int sockfd,new_fd;		// Socket Handle
	struct sockaddr_in my_addr;		// structure of server addr
	struct sockaddr_in their_addr;	// structure of client addr
	int sin_size;
	char str[1024];
	char *p = NULL;

	sockfd=socket(AF_INET,SOCK_STREAM,0);	// Set up Socket
	if(sockfd==-1){
		printf("socket failed:%d",errno);
		return -1;
	}
	my_addr.sin_family=AF_INET;			// AF_INET --> receive trasmission
	my_addr.sin_port=htons(PORT);		// set port number
	my_addr.sin_addr.s_addr=htonl(INADDR_ANY);		// INADDR_ANY--> local IP
	bzero(&(my_addr.sin_zero),8);		// set other valeus=0
	if(bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))<0){		// Bind addr structure with Socket.
		printf("bind error");
		return -1;
	}
	listen(sockfd,BACKLOG);		// Start Listening
	printf("Server: Wait coneection and send message\n");
	sin_size=sizeof(struct sockaddr_in);
	new_fd=accept(sockfd,(struct sockaddr*)&their_addr,&sin_size);
	// accept(handle, received_addr, size of )
	if(new_fd==-1){
		printf("receive failed");
	}
	else{
		printf("connection success!\n---------\n");
		while(1){
			printf("Input str u want to send:");
			scanf("%[^\n]", str);
			p = Des_Encrypt(str);			// Encrypt str to DES code
			send(new_fd, p, MAX_DATA, 0);		// Send code
			printf("Send:\033[40;36m%s\033[0m\n", str);
#if SHOW_DES
			printf("Code:\033[40;33m%s\033[0m\n", p);
#endif
			memset(str, 0, MAX_DATA); 
			// avoid invalid char stored in buffer. It ensures user input string in loop.
			getchar();
			sleep(2);
		}
	}
	return 0;
}
