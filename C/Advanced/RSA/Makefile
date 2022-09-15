
CC := gcc

SRC_DIR := src

RSA_FILE := $(SRC_DIR)/*.c

CFLAGS := -I$(SRC_DIR)

all: test_rsa

test_rsa:
	$(CC) $(CFLAGS) $(RSA_FILE) -o $@ -lm

clean:
	rm -f test_rsa

