#include "config.h"


void Chat_server()
{
	int chat_fd = 0, max_fd = 0, server_fd = -1;
	int sel_code = 0, rec_code = 0;
	struct sockaddr_in cli_addr;
	struct timeval tv;
	char buf[MAX_DATA];
	fd_set rfds;
	char *ser_encry = NULL, *ser_context = NULL;


	while(1){
		if(server_fd < 0){
			/* INADDR_ANY --> local IP */
			server_fd = listen_socket(0, PORT, "lo");
			if(server_fd == -1)
				return;

			printf("[Server] Start listening...\n");
		}

		while(1){
			chat_fd = accept(server_fd, (struct sockaddr *) &cli_addr, &sin_size);
			if(chat_fd == -1)
				printf("Accept failed: %s\n", strerror(errno));
			else
				printf("[Client Info] %s:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

			while(1){
				FD_ZERO(&rfds);
				FD_SET(0, &rfds);
				FD_SET(chat_fd, &rfds);

				/* Find the max fd */
				max_fd = 0;
				if(max_fd < chat_fd)
					max_fd = chat_fd;
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
							printf("Server terminate the chat\n");
							break;
						}
#if USE_DES
						/* Encrypt the info with DES. */
						ser_encry = Des_Encrypt(buf);
#if TEST
						printf("Code:\033[40;33m%s\033[0m\n", ser_encry);
#endif
						if(send(chat_fd, ser_encry, strlen(ser_encry), 0) <= 0){
#else
						if(send(chat_fd, buf, strlen(buf), 0) <= 0){
#endif
							printf("Message failed to send!\n");
						}
					}
					/* detect whether client send message. */
					if(FD_ISSET(chat_fd, &rfds)){
						memset(buf, 0, sizeof(buf));

						rec_code = recv(chat_fd, buf, MAX_DATA, 0);
						if(rec_code > 0){
#if USE_DES
							/* Decrypt code to context with DES. */
#if TEST
							printf("Code:\033[40;33m%s\033[0m\n", buf);
#endif
							ser_context = Des_Decrypt(buf);
							printf("[Client] \033[40;36m%s\033[0m\n", ser_context);
#else
							printf("[Client] \033[40;36m%s\033[0m\n", buf);
#endif
						}else{
							if(rec_code < 0)
								printf("Receive failed: %s\n", strerror(errno));
							else
								printf("Client quit the connection, so chat ends!\n");
							break;
						}
					}
				}
			}
			close(chat_fd);
			printf("Quit chat? [Y/N] ");
			bzero(buf, MAX_DATA);
			fgets(buf, MAX_DATA, stdin);
			if(!strncmp(buf, "y", 1) || !strncmp(buf, "Y", 1)){
				printf("\nQuit from chat!\n");
				break;
			}
		}
		close(server_fd);
		server_fd = -1;

		scanf("Quit program? [y/n] %s", buf);
		if(!strncmp(buf, "y", 1) || !strncmp(buf, "Y", 1))
			break;
	}

}


int main()
{

	Chat_server();

	return 0;
}

