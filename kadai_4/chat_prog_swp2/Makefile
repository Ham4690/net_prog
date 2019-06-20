#
# Makefile for quiz_server and quiz_client
#
MYLIBDIR=../netlib
MYLIB=-lmynet
CFLAGS=-I${MYLIBDIR} -L${MYLIBDIR}
OBJS=chat.o chat_server.o chat_client.o chat_util.o question.o chat_common.o

all: quiz

quiz: ${OBJS}
	${CC} ${CFLAGS} -o $@ $^ ${MYLIB}

clean:
	${RM} *.o quiz *~