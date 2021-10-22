char2ascii: char2ascii.o
	gcc -g -m32 -Wall -o char2ascii char2ascii.o
	rm char2ascii.o

char2ascii.o: char2ascii.c
	gcc -g -m32 -Wall -c -o char2ascii.o char2ascii.c

.PHONY: clean
	rm -rf ./*.o main