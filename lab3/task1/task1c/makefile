bcmp: task1c.o
	gcc -g -m32 -Wall -o bcmp task1c.o
	rm task1c.o

task1c.o: task1c.c
	gcc -g -m32 -Wall -c -o task1c.o task1c.c

.PHONY: clean

clean:
	rm -f *.o bcmp