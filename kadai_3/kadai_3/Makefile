#CC := gcc
MYLIBD = -lmynet
CFLAGS := -Wall -Wextra -I../mynet -L../mynet

all:kadai_3_a

kadai_3_a:kadai_3_a.c
	${CC} ${CFLAGS} -o $@ $^ ${MYLIBD}

clean:
	${RM} kadai_3_a*
