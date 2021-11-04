bcmp: task1a.o
	gcc -g -m32 -Wall -o bcmp task1a.o
	rm task1a.o

task1a.o: task1a.c
	gcc -g -m32 -Wall -c -o task1a.o task1a.c

.PHONY: clean

clean:
	rm -f *.o bcmp