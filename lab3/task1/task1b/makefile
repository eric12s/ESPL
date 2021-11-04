bcmp: task1b.o
	gcc -g -m32 -Wall -o bcmp task1b.o
	rm task1b.o

task1b.o: task1b.c
	gcc -g -m32 -Wall -c -o task1b.o task1b.c

.PHONY: clean

clean:
	rm -f *.o bcmp