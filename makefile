CC = gcc
CFLAGS = -Wall
BUILD_DIR = dist

all: $(BUILD_DIR) server client sungka

$(BUILD_DIR):
	mkdir -p $@

server: src/server.c src/connection.c
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/server

client: src/client.c src/connection.c
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/client

sungka:
	$(CC) $(CFLAGS) ./src/sungka.c -o $(BUILD_DIR)/sungka

clean: 
	rm -rf $(BUILD_DIR)