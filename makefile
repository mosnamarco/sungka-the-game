CC = gcc
CFLAGS = -Wall

all: server client

server: server.c
	$(CC) $(CFLAGS) server.c -o server

client: client.c
	$(CC) $(CLFAGS) client.c -o client

clean: 
	rm -f server
	rm -f client