CC = gcc
CFLAGS = -Wall

all: server client sungka

server: ./src/server.c
	$(CC) $(CFLAGS) ./src/server.c -o ./dist/server

client: ./src/client.c
	$(CC) $(CLFAGS) ./src/client.c -o ./dist/client

sungka: ./src/sungka.c
	$(CC) $(CLFAGS) ./src/sungka.c -o ./dist/sungka

clean: 
	rm -f ./dist/server
	rm -f ./dist/client
	rm -f ./dist/sungka