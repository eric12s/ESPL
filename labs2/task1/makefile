output: addresses.o
	gcc -g -m32 -Wall -o addresses addresses.o
	rm addresses.o

addresses.o: addresses.c
	gcc -g -m32 -Wall -c -o addresses.o addresses.c

.PHONY: clean

clean:
	rm *.o addresses