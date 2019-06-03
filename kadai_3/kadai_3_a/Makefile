#CC := gcc
MYLIBD = -lmynet
CFLAGS := -I../mynet -L../mynet

all:kadai_3_a

kadai_3_a:kadai_3_a.c
	${CC} ${CFLAGS} -o $@ $^ ${MYLIBD}

clean:
	${RM} kadai_3*
