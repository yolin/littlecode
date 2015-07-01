SERVER_OBJS=tcpserver.o
CLIENT_OBJS=tcpclient.o
CFLAGS+=-lcurses

build: tcpserver tcpclient

tcpserver: ${SERVER_OBJS}
	${CC} ${CFLAGS} -o $@ ${SERVER_OBJS}

tcpclient: ${CLIENT_OBJS}
	${CC} ${CFLAGS} -o $@ ${CLIENT_OBJS}
