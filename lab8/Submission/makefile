all: patch task0 task1 task2 task3

task0: task0.o
	gcc -g -m32 -Wall -o task0 task0.o
	rm -f task0.0

task0.o: task0.c
	gcc -g -m32 -Wall -c -o task0.o task0.c

task1: task1.o
	gcc -g -m32 -Wall -o task1 task1.o
	rm -f task1.0

task1.o: task1.c
	gcc -g -m32 -Wall -c -o task1.o task1.c

task2: task2.o
	gcc -g -m32 -Wall -o task2 task2.o
	rm -f task2.o

task2.o: task2.c
	gcc -g -m32 -Wall -c -o task2.o task2.c

task3: task3.o
	gcc -g -m32 task3.o -o task3

task3.o: task3.c
	gcc -g -m32 -fno-pie -c -o task3.o task3.c

patch: patch.o
	gcc -g -m32 patch.o -o patch

patch.o: patch.c
	gcc -g -m32 -fno-pie -c -o patch.o patch.c

.PHONY: clean

clean:
	rm -f *.o task0 task1 task2 task3 patch