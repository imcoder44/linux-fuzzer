CC=gcc
CFLAGS=-Wall -Wextra -O2
OBJS=main.o fuzzer.o executor.o logger.o utils.o

all: fuzzer

fuzzer: $(OBJS)
	$(CC) $(CFLAGS) -o fuzzer $(OBJS)

main.o: main.c fuzzer.h executor.h logger.h utils.h
fuzzer.o: fuzzer.c fuzzer.h executor.h logger.h utils.h
executor.o: executor.c executor.h
logger.o: logger.c logger.h
utils.o: utils.c utils.h

clean:
	rm -f *.o fuzzer
