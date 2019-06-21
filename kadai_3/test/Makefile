#CC := gcc
MYLIBD = -lmynet
CFLAGS := -I../mynet -L../mynet

all:test

test:test.c
	${CC} ${CFLAGS} -o $@ $^ ${MYLIBD}

clean:
	${RM} test*
