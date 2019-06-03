#
# Makefile for tcp_echo
#

MYLIB=-lmynet -lpthread
CFLAGS=-I../mynet -L../mynet

all: kadai3 

kadai3: kadai3.c
	${CC} ${CFLAGS} -o $@ $^ ${MYLIB}

clean:
	${RM} kadai3 

