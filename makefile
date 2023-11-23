CC = gcc
CFLAGS = -Wall
BUILD_DIR = dist

all: $(BUILD_DIR) server client #sungka

$(BUILD_DIR):
	mkdir -p $@

server: src/server.c src/connection.c ./src/sungka.c
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/server

client: src/client.c src/connection.c ./src/sungka.c
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/client
	
clean: 
	rm -rf $(BUILD_DIR)