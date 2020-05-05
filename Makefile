TARGET = filesort
OBJS = filesort.o
SRCS = filesort.c filesort.h
CC = cc
SOURCE_FILE = /tmp/111.zip
TARGET_FILE = /tmp/222.zip
ALL : ${TARGET}

${TARGET} : ${OBJS}
	${CC} -g -o ${TARGET} ${OBJS}

${OBJS} : ${SRCS}
	${CC} -g -c $< -o $@
clean:
	-rm -f ${OBJS}
	-rm -f ${TARGET}
run:
	-rm -f ${TARGET_FILE}
	date&&${TARGET} ${SOURCE_FILE} ${TARGET_FILE}&&date
delete:
	-rm -f ${TARGET_FILE}
