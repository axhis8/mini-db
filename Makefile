CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

SRC = $(wildcard src/*.c)
BIN = bin/mini-db

.PHONY: all clean

all: $(BIN)

$(BIN): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf bin
