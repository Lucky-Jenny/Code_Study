#include "config.h"


void Chat_client()
{
	int max_fd = 0, client_fd = -1;
	int sel_code = 0, rec_code = 0;
	struct timeval tv;
	char buf[MAX_DATA];
	fd_set rfds;
	char *cli_encry = NULL, *cli_context = NULL;

	/* 0 --> INADDR_ANY */
	client_fd = connect_socket(0, PORT);
	if(client_fd == -1)
		return;

	printf("[Client] Start connection...\n");

	while(1){
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		FD_SET(client_fd, &rfds);

		/* Find the max fd */
		max_fd = 0;
		if(max_fd < client_fd)
			max_fd = client_fd;
		/* Set timeout */
		tv.tv_sec = 6;
		tv.tv_usec = 0;

		sel_code = select(max_fd + 1, &rfds, NULL, NULL, &tv);
		if(sel_code == -1){
			printf("select failed: %s\n", strerror(errno));
			break;
#if TEST
		}else if(sel_code == 0){
			printf("Waiting...\n");
			continue;
#endif
		}else{
			/* detect whether user has input */
			if(FD_ISSET(0, &rfds)){
				memset(buf, 0, sizeof(buf));
				fgets(buf, MAX_DATA, stdin);

				if(!strncasecmp(buf, "quit", 4)){
					printf("Client terminate the chat\n");
					break;
				}
#if USE_DES
				/* Encrypt the info with DES. */
				cli_encry = Des_Encrypt(buf);
#if TEST
				printf("Code:\033[40;33m%s\033[0m\n", cli_encry);
#endif
				if(send(client_fd, cli_encry, strlen(cli_encry), 0) <= 0){
#else
				if(send(client_fd, buf, strlen(buf), 0) <= 0){
#endif
					printf("Message failed to send!\n");
					break;
				}
			}

			/* detect whether server sent message. */
			if(FD_ISSET(client_fd, &rfds)){
				memset(buf, 0, sizeof(buf));
				rec_code = recv(client_fd, buf, MAX_DATA, 0);
				if(rec_code > 0){
#if USE_DES
					/* Decrypt code to context with DES. */
#if TEST
					printf("Code:\033[40;33m%s\033[0m\n", buf);
#endif
					cli_context = Des_Decrypt(buf);
					printf("[Server] \033[40;36m%s\033[0m\n", cli_context);
#else
					printf("[Server] \033[40;36m%s\033[0m\n", buf);
#endif
				}else{
					if(rec_code < 0)
						printf("Receive failed: %s\n", strerror(errno));
					else
						printf("Server quit the connection, so chat ends!\n");
					break;
				}
			}
		}
	}
	close(client_fd);

}


int main()
{
	Chat_client();
	return 0;
}

