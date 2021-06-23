# In multiple files of a project, it is a must to use 'Makefile'.
# This is also my first Makefile !!!

INCLUDE := DES
CC := gcc

SERVER_FILE := server.c $(INCLUDE)/DES.c
CLIENT_FILE := client.c $(INCLUDE)/DES.c

# U should do 'make' after 'clean'.
all: server client

server:
	$(CC) $(SERVER_FILE) -o $@
client:
	$(CC) $(CLIENT_FILE) -o $@
%.o: %.c
	$(CC) -c $<

clean:
	rm -f *.o
	rm -f server client


