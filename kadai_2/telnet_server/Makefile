MYLIBD = -lmynet
CFLAGS := -I../mynet -L../mynet

all: tcp_server

tcp_server:tcp_server.c
	${CC} ${CFLAGS} -o $@ $^ ${MYLIBD}

clean:
	${RM} tcp_server
