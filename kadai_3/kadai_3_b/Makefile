#
# Makefile for tcp_echo
#

MYLIB=-lmynet -lpthread
CFLAGS=-I../mynet -L../mynet

all: kadai_3_b

kadai_3_b: kadai_3_b.c
	${CC} ${CFLAGS} -o $@ $^ ${MYLIB}

clean:
	${RM} kadai_3_b

