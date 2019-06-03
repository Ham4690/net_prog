#
# Makefile for tcp_echo
#

MYLIB=-lmynet
CFLAGS=-I../mynet -L../mynet

all: fork_server fork_client

fork_server: fork_server.c
	${CC} ${CFLAGS} -o $@ $^ ${MYLIB}

fork_client: tcp_client.c
	${CC} ${CFLAGS} -o $@ $^ ${MYLIB}

clean:
	${RM} fork_server

