all: client server

client: client.c
	gcc -Wall -Wextra -o $@ $^

server: server.c
	gcc -Wall -Wextra -o $@ $^
