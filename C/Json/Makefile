
CC := gcc

DIR_INC := ./include
JSON_SOURCE := ./*.c ${DIR_INC}/*.c

CFLAGS += -l${DIR_INC}

all: test_json

test_json:
	$(CC) $(CFLAGS) $(JSON_FILE) -o $@ -lm

clean:
	rm -f test_json

