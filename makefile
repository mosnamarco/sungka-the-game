CC = gcc
CFLAGS = -Wall
BUILD_DIR = dist

all: $(BUILD_DIR) server client sungka

$(BUILD_DIR):
	mkdir -p $@

server:
	$(CC) $(CFLAGS) ./src/server.c -o $(BUILD_DIR)/server

client:
	$(CC) $(CFLAGS) ./src/client.c -o $(BUILD_DIR)/client

sungka:
	$(CC) $(CFLAGS) ./src/sungka.c -o $(BUILD_DIR)/sungka

clean: 
	rm -rf $(BUILD_DIR)