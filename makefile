CC = gcc
CFLAGS = -Wall

all: server client sungka

server: server.c
	$(CC) $(CFLAGS) server.c -o server

client: client.c
	$(CC) $(CLFAGS) client.c -o client

sungka: sungka.c
	$(CC) $(CLFAGS) sungka.c -o sungka

clean: 
	rm -f server
	rm -f client