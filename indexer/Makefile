OBJS	= main.o theTrie.o utils.o opcoes.o
SOURCE	= main.c theTrie.c utils.c opcoes.c
HEADER	= theTrie.h utils.h opcoes.h
OUT	= indexer
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) 

main.o: main.c
	$(CC) $(FLAGS) main.c 

theTrie.o: theTrie.c
	$(CC) $(FLAGS) theTrie.c

utils.o: utils.c
	$(CC) $(FLAGS) utils.c

opcoes.o: opcoes.c
	$(CC) $(FLAGS) opcoes.c


clean:
	rm -f $(OBJS) $(OUT)