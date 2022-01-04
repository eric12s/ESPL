all: examine

examine: examine.o
	gcc -g -m32 -Wall -o examine examine.o
	rm -f examine.0
examine.o: examine.c
	gcc -g -m32 -Wall -c -o examine.o examine.c

.PHONY: clean

clean:
	rm -f *.o examine