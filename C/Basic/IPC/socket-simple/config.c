#include "config.h"

int sin_size = sizeof(struct sockaddr_in);


int connect_socket(char *target_ip, int port)
{
	int fd = 0;
	struct sockaddr_in ser_addr;

	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(fd < 0){
		printf("Socket failed: %s\n", strerror(errno));
		return -1;
	}

	/* Init server address */
	memset(&ser_addr, 0, sin_size);
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(port);
	if(target_ip != NULL){
		inet_aton(target_ip, &ser_addr.sin_addr);
	}

	/* Start connect */
	if(connect(fd, (struct sockaddr *)&ser_addr, sin_size) == -1){
		printf("Connect failed: %s\n", strerror(errno));
		return -1;
	}

	return fd;
}

int listen_socket(char *ip, int port, char *interface)
{
	int fd = 0, n = 0;
	struct sockaddr_in addr;
#if TEST
	printf("[IP] %s [Port] %d [interface] %s\n", ip, port, interface);
#endif
	/* 
	 AF_INET :       IPv4
	 SOCKET_STREAM:  Byte stream
	 0: Do not specify the protocol, decided by Server provider.
	*/
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(fd < 0){
		printf("Socket failed: %s\n", strerror(errno));
		return -1;
	}

	/* Init the address */
	memset(&addr, 0, sin_size);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if(ip != NULL){
		if(inet_aton(ip, &addr.sin_addr) == -1)
			addr.sin_addr.s_addr = INADDR_ANY;
	}

	/* Allow re-use local address in bind(). */
	if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&n, sizeof(n)) == -1){
		printf("re-use failed: %s\n", strerror(errno));
		close(fd);
		return -1;
	}
	/* Send method : Broadcast */
	if(setsockopt(fd, SOL_SOCKET, SO_BROADCAST, (char *)&n, sizeof(n)) == -1){
		printf("broadcast failed: %s\n", strerror(errno));
		close(fd);
		return -1;
	}
	/*
	 SO_BINDTODEVICE : Bind this socket to specified interface.
	 Comment because it requires root permission. (For convenience)
	*/
/*	if(setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE, (char *)&interface, sizeof(n)) == -1){
		printf("bind-to-device failed: %s\n", strerror(errno));
		close(fd);
		return -1;
	}
*/
	if(bind(fd, (struct sockaddr *)&addr, sin_size) == -1){
		printf("Bind failed: %s\n", strerror(errno));
		close(fd);
		return -1;
	}

	/* Start listening */
	listen(fd, BACKLOG);

	return fd;
}


