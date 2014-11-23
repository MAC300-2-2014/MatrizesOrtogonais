CC = gcc 
CFLAGS = -Wall -pedantic -Wno-unused-result  -lm

all: main
	./main

main: QRdecomposition.o utils.o main.o
	$(CC) main.o QRdecomposition.o utils.o -o main 

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

QRdecomposition.o: QRdecomposition.c QRdecomposition.h 
	$(CC) $(CFLAGS) -c QRdecomposition.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c


clean:
	rm *.o 