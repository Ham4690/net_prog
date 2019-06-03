#
# Makefile for tcp_echo
#

MYLIB=-lmynet -lpthread
CFLAGS=-I../mynet -L../mynet

all: echo_server3th

echo_server3th: echo_server3th.c
	${CC} ${CFLAGS} -o $@ $^ ${MYLIB}

clean:
	${RM} echo_server3th 

