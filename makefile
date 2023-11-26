CC = gcc
CFLAGS = -Wall
BUILD_DIR = dist

all: $(BUILD_DIR) server client #sungka

$(BUILD_DIR):
	mkdir -p $@

server: ./src/sungka.c src/server.c src/connection.c 
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/server

client: ./src/sungka.c src/client.c src/connection.c 
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/client
	
clean: 
	rm -rf $(BUILD_DIR)