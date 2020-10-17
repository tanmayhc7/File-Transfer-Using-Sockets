CC=gcc
CFLAGS= -g -Wall 
RM=rm -rf *.dSYM *.o
all: server_ftp_udp.c
	$(CC) $(CFLAGS) -o server command_handler.c command_handler.h server_ftp_udp.c

clean:
	$(RM) server
