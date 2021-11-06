bcmp: task2.o
	gcc -g -m32 -Wall -o bcmp task2.o
	rm task2.o

task2.o: task2.c
	gcc -g -m32 -Wall -c -o task2.o task2.c

.PHONY: clean

clean:
	rm -f *.o bcmp