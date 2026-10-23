CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -g

SRC = $(wildcard src/*.c)
INC = $(wildcard include/*.h)
BIN = bin/mini-db

.PHONY: all clean

all: $(BIN)

$(BIN): $(SRC) $(INC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf bin
