CC  = gcc
CFLAGS  = -std=c11 -w
RM  = rm -r
NAME = HomeWork3MarkTikhonov
BIN = bin
SOURCE = src
OBJ = ${BIN}/obj
ARGV = 20 2

DEBUG = 0

ifeq (${DEBUG}, 1)
CFLAGS += -g -O0
else
CFLAGS += -O3
endif

default:    all

all: build execute
 
build:   
	 
	mkdir -p ${OBJ}
	${CC} -c ${CFLAGS}  ${SOURCE}/${NAME}.c -o ${OBJ}/${NAME}.o
	${CC} ${OBJ}/${NAME}.o -o ${BIN}/${NAME}

execute:
	${BIN}/${NAME} ${ARGV}

	

clean:
	${RM} ${BIN}