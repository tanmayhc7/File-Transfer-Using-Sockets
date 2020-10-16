CC=gcc
CFLAGS= -g -Wall 
RM=rm -rf *.dSYM
all: client_ftp_udp.c
	$(CC) $(CFLAGS) -o client command_handler.c command_handler.h client_ftp_udp.c

clean:
	$(RM) client
