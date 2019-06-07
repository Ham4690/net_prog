#CC := gcc
MYLIBD = -lmynet
CFLAGS := -I../mynet -L../mynet

all:kadai_3

kadai_3:kadai_3.c
	${CC} ${CFLAGS} -o $@ $^ ${MYLIBD}

clean:
	${RM} kadai_3*
