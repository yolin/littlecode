OBJS1=inotify.o
OBJS2=inotify_improve.o

build: inotify inotify_improve

inotify: ${OBJS1}
	${CC} ${CFLAGS} -o $@ ${OBJS1}

inotify_improve: ${OBJS2}
	${CC} ${CFLAGS} -o $@ ${OBJS2}

